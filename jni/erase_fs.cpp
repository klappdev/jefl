#include <iostream>

#if __has_include(<filesystem>)
# include <filesystem>
  namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
# include <experimental/filesystem>
  namespace fs = std::experimental::filesystem;
#else
# error "missing <filesystem>"
#endif

#include "org_kl_erase_EraseFS.h"
#include "erase/erase_content.hpp"

#include "state/overwrite_mode.hpp"
#include "util/log_util.hpp"

static jint JNI_VERSION = JNI_VERSION_1_8;

static jclass exception_class;
static jclass override_mode_class;

static jfieldID simple_mode_id;
static jmethodID name_id;

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* jvm, void* reserved) {
	JNIEnv* env;
	jclass local_clazz;

	if (jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION) != JNI_OK) {
		return JNI_ERR;
	}

	local_clazz = env->FindClass("org/kl/error/EraseException");
	exception_class = (jclass) env->NewGlobalRef(local_clazz);
	env->DeleteLocalRef(local_clazz);

	local_clazz = env->FindClass("org/kl/state/OverwrideMode");
	override_mode_class = (jclass) env->NewGlobalRef(local_clazz);
	env->DeleteLocalRef(local_clazz);

	simple_mode_id = env->GetStaticFieldID(override_mode_class, "SIMPLE_MODE", "Lorg/kl/state/OverwrideMode;");
	name_id = env->GetMethodID(override_mode_class, "name", "()Ljava/lang/String;");

	return JNI_VERSION;
}

extern "C" JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *jvm, void *reserved) {
	JNIEnv* env;

	if (jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION)) {
		return;
	}

	env->DeleteGlobalRef(override_mode_class);
	env->DeleteGlobalRef(exception_class);
}

static jobject take_default_mode(JNIEnv *env);
static kl::overwrite_mode take_mode(JNIEnv *env, jobject mode_object);

extern "C" JNIEXPORT jboolean JNICALL Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2Lorg_kl_state_OverwrideMode_2
(JNIEnv* env, jclass clazz, jstring path, jobject mode_object) {
	const char* temp = env->GetStringUTFChars(path, nullptr);
	const auto& file = fs::path(temp);

	kl::erase_content eraser;

	if (!fs::exists(file)) {
		env->ThrowNew(exception_class, "File doesn't exist");
		env->ReleaseStringUTFChars(path, temp);

		return false;
	}

	if (!fs::is_regular_file(file)) {
		env->ThrowNew(exception_class, "Path doesn't regular file or symlink");
		env->ReleaseStringUTFChars(path, temp);

		return false;
	}

	if (!eraser.check_permision(file, fs::status(file).permissions())) {
		env->ThrowNew(exception_class, "File hasn't enough permision (maybe not user)");
		env->ReleaseStringUTFChars(path, temp);

		return false;
	}

	if (!eraser.init_erase_etry(file, take_mode(env, mode_object))) {
		env->ThrowNew(exception_class, "init erase entry fail");
		env->ReleaseStringUTFChars(path, temp);

		return false;
	}

	if (!eraser.overwrite()) {
		env->ThrowNew(exception_class, "overwrite entry fail");
		env->ReleaseStringUTFChars(path, temp);

		return false;
	}

	try {
		fs::resize_file(file, 0);
	} catch (fs::filesystem_error& e) {
		env->ThrowNew(exception_class, "truncate file fail");
		env->ReleaseStringUTFChars(path, temp);

		return false;
	}

	if (!eraser.remove(file)) {
		env->ThrowNew(exception_class, "change name fail");
		env->ReleaseStringUTFChars(path, temp);

		return false;
	}

	env->ReleaseStringUTFChars(path, temp);

	return true;
}

extern "C" JNIEXPORT jboolean JNICALL Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2
(JNIEnv* env, jclass clazz, jstring path) {
	return Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2Lorg_kl_state_OverwrideMode_2
		   (env, clazz, path, take_default_mode(env));
}

extern "C" JNIEXPORT jboolean JNICALL Java_org_kl_erase_EraseFS_eraseFiles__Lorg_kl_state_OverwrideMode_2_3Ljava_lang_String_2
(JNIEnv* env, jclass clazz, jobject mode_object, jobjectArray paths) {
	size_t length = env->GetArrayLength(paths);

	for (int i = 0; i < length; i++) {
		jstring path = (jstring) env->GetObjectArrayElement(paths, i);

		if (!Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2Lorg_kl_state_OverwrideMode_2(env, clazz, path, mode_object)) {
			return false;
		}
	}

	return true;
}

extern "C" JNIEXPORT jboolean JNICALL Java_org_kl_erase_EraseFS_eraseFiles___3Ljava_lang_String_2
(JNIEnv* env, jclass clazz, jobjectArray paths) {
	return Java_org_kl_erase_EraseFS_eraseFiles__Lorg_kl_state_OverwrideMode_2_3Ljava_lang_String_2
		   (env, clazz, take_default_mode(env), paths);
}

extern "C" JNIEXPORT jboolean JNICALL Java_org_kl_erase_EraseFS_eraseDirectory__Ljava_lang_String_2Lorg_kl_state_OverwrideMode_2Z
(JNIEnv* env, jclass clazz, jstring path, jobject mode_object, jboolean recursived) {
	const char* temp = env->GetStringUTFChars(path, nullptr);
	const auto& folder = fs::path(temp);
	jstring file_path = nullptr;

	if (!fs::exists(folder)) {
		env->ThrowNew(exception_class, "Directory doesn't exist");

		return false;
	}

	if (!fs::is_directory(folder)) {
		env->ThrowNew(exception_class, "Path doesn't directory");

		return false;
	}

	if (recursived) {
		for (const auto& item : fs::recursive_directory_iterator(folder)) {
			file_path = env->NewStringUTF(item.path().c_str());

			if (!fs::is_directory(item.path())) {
				if (!Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2Lorg_kl_state_OverwrideMode_2(env, clazz, file_path, mode_object)) {
					env->ReleaseStringUTFChars(path, temp);
					return false;
				}
			}
		}
	} else {
		for (const auto& item : fs::directory_iterator(folder)) {
			file_path = env->NewStringUTF(item.path().c_str());

			if (!Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2Lorg_kl_state_OverwrideMode_2(env, clazz, file_path, mode_object)) {
				env->ReleaseStringUTFChars(path, temp);
				return false;
			}
		}
	}

	env->ReleaseStringUTFChars(path, temp);

	return true;
}

extern "C" JNIEXPORT jboolean JNICALL Java_org_kl_erase_EraseFS_eraseDirectory__Ljava_lang_String_2Z
(JNIEnv* env, jclass clazz, jstring path, jboolean recursived) {
	return Java_org_kl_erase_EraseFS_eraseDirectory__Ljava_lang_String_2Lorg_kl_state_OverwrideMode_2Z
		   (env, clazz, path, take_default_mode(env), recursived);
}

jobject take_default_mode(JNIEnv *env) {
	jobject simple_mode_object = env->GetStaticObjectField(override_mode_class, simple_mode_id);

	return simple_mode_object;
}

kl::overwrite_mode take_mode(JNIEnv *env, jobject mode_object) {
	kl::overwrite_mode mode;

	jstring name = (jstring) env->CallObjectMethod(mode_object, name_id);

	const char* temp = env->GetStringUTFChars(name, nullptr);

	if (std::strcmp(temp, "SIMPLE_MODE") == 0) {
		mode = kl::overwrite_mode::SIMPLE_MODE;
	}

	if (std::strcmp(temp, "DOE_MODE") == 0) {
		mode = kl::overwrite_mode::DOE_MODE;
	}

	if (std::strcmp(temp, "RCMP_MODE") == 0) {
		mode = kl::overwrite_mode::RCMP_MODE;
	}

	if (std::strcmp(temp, "OPENBSD_MODE") == 0) {
		mode = kl::overwrite_mode::OPENBSD_MODE;
	}

	if (std::strcmp(temp, "DOD_MODE") == 0) {
		mode = kl::overwrite_mode::DOD_MODE;
	}

	if (std::strcmp(temp, "GUTMAN_MODE") == 0) {
		mode = kl::overwrite_mode::GUTMAN_MODE;
	}

	kl::log_util::debug("mode: ", temp);

	env->ReleaseStringUTFChars(name, temp);

	return mode;
}
