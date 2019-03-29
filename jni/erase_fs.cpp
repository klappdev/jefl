#include <iostream>
#include <filesystem>

#include "org_kl_erase_EraseFS.h"
#include "erase/erase_content.hpp"
#include "state/overwrite_mode.hpp"

namespace fs = std::filesystem;

static jobject take_default_mode(JNIEnv *env);
static kl::overwrite_mode take_mode(JNIEnv *env, jobject mode_object);

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2Lorg_kl_state_OverwrideMode_2(JNIEnv* env, jclass clazz, jstring path, jobject mode_object) {
	jclass exception = env->FindClass("org/kl/error/EraseException");

	const char* temp = env->GetStringUTFChars(path, nullptr);
	const auto& file = fs::path(temp);

	kl::erase_content eraser;

	if (!fs::exists(file)) {
		env->ThrowNew(exception, "File doesn't exist");
		env->ReleaseStringUTFChars(path, temp);

		return false;
	}

	if (!fs::is_regular_file(file)) {
		env->ThrowNew(exception, "Path doesn't regular file or symlink");
		env->ReleaseStringUTFChars(path, temp);

		return false;
	}

	if (!eraser.check_permision(file, fs::status(file).permissions())) {
		env->ThrowNew(exception, "File hasn't enough permision (maybe not user)");
		env->ReleaseStringUTFChars(path, temp);

		return false;
	}

	if (!eraser.init_erase_etry(file, take_mode(env, mode_object))) {
		env->ThrowNew(exception, "init erase entry fail");
		env->ReleaseStringUTFChars(path, temp);

		return false;
	}

	if (!eraser.overwrite()) {
		env->ThrowNew(exception, "overwrite entry fail");
		env->ReleaseStringUTFChars(path, temp);

		return false;
	}

	try {
		fs::resize_file(file, 0);
	} catch (fs::filesystem_error& e) {
		env->ThrowNew(exception, "truncate file fail");
		env->ReleaseStringUTFChars(path, temp);

		return false;
	}

	if (!eraser.remove(file)) {
		env->ThrowNew(exception, "change name fail");
		env->ReleaseStringUTFChars(path, temp);

		return false;
	}

	env->ReleaseStringUTFChars(path, temp);

	return true;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring path) {
	return Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2Lorg_kl_state_OverwrideMode_2(env, clazz, path, take_default_mode(env));
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseFiles__Lorg_kl_state_OverwrideMode_2_3Ljava_lang_String_2(JNIEnv* env, jclass clazz, jobject mode_object, jobjectArray paths) {
	size_t length = env->GetArrayLength(paths);

	for (int i = 0; i < length; i++) {
		jstring path = (jstring) env->GetObjectArrayElement(paths, i);

		if (!Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2Lorg_kl_state_OverwrideMode_2(env, clazz, path, mode_object)) {
			return false;
		}
	}

	return true;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseFiles___3Ljava_lang_String_2(JNIEnv* env, jclass clazz, jobjectArray paths) {
	return Java_org_kl_erase_EraseFS_eraseFiles__Lorg_kl_state_OverwrideMode_2_3Ljava_lang_String_2(env, clazz, take_default_mode(env), paths);
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseDirectory__Ljava_lang_String_2Lorg_kl_state_OverwrideMode_2Z(JNIEnv* env, jclass clazz, jstring path, jobject mode_object, jboolean recursived) {
	const char* temp = env->GetStringUTFChars(path, nullptr);
	const auto& folder = fs::path(temp);
	jstring file_path = nullptr;

	if (!fs::exists(folder)) {
		jclass exception = env->FindClass("org/kl/error/EraseException");
		env->ThrowNew(exception, "Directory doesn't exist");

		return false;
	}

	if (!fs::is_directory(folder)) {
		jclass exception = env->FindClass("org/kl/error/EraseException");
		env->ThrowNew(exception, "Path doesn't directory");

		return false;
	}

	if (recursived) {
		for (const auto& item : fs::recursive_directory_iterator(folder)) {
			file_path = env->NewStringUTF(item.path().c_str());

			if (!Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2Lorg_kl_state_OverwrideMode_2(env, clazz, file_path, mode_object)) {
				return false;
			}
		}
	} else {
		for (const auto& item : fs::directory_iterator(folder)) {
			file_path = env->NewStringUTF(item.path().c_str());

			if (!Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2Lorg_kl_state_OverwrideMode_2(env, clazz, file_path, mode_object)) {
				return false;
			}
		}
	}

	env->ReleaseStringUTFChars(path, temp);

	return true;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseDirectory__Ljava_lang_String_2Z(JNIEnv* env, jclass clazz, jstring path, jboolean recursived) {
	return Java_org_kl_erase_EraseFS_eraseDirectory__Ljava_lang_String_2Lorg_kl_state_OverwrideMode_2Z(env, clazz, path, take_default_mode(env), recursived);
}

jobject take_default_mode(JNIEnv *env) {
	jclass mode_class = env->FindClass("org/kl/state/OverwrideMode");
	jfieldID simple_mode_id = env->GetStaticFieldID(mode_class, "SIMPLE_MODE", "Lorg/kl/state/OverwrideMode;");
	jobject simple_mode_object = env->GetStaticObjectField(mode_class, simple_mode_id);

	return simple_mode_object;
}

kl::overwrite_mode take_mode(JNIEnv *env, jobject mode_object) {
	kl::overwrite_mode mode;

	jclass override_mode_class = env->GetObjectClass(mode_object);
	jmethodID name_id = env->GetMethodID(override_mode_class, "name", "()Ljava/lang/String;");
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

	std::cout << "mode: " << temp << std::endl;

	env->ReleaseStringUTFChars(name, temp);

	return mode;
}







