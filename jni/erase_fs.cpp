#include <iostream>
#include <filesystem>

#include "org_kl_erase_EraseFS.h"
#include "erase/erase_content.hpp"
#include "state/overwrite_mode.hpp"

namespace fs = std::filesystem;

static jobject take_default_mode(JNIEnv *env);

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2Lorg_kl_state_OverrideMode_2(JNIEnv* env, jclass clazz, jstring path, jobject mode_object) {
	const char* temp = env->GetStringUTFChars(path, nullptr);
	const auto& file = fs::path(temp);

	if (!fs::exists(file)) {
		jclass exception = env->FindClass("org/kl/error/EraseException");
		env->ThrowNew(exception, "File doesn't exist");

		return false;
	}

	if (!fs::is_symlink(file) || !fs::is_regular_file(file)) {
		jclass exception = env->FindClass("org/kl/error/EraseException");
		env->ThrowNew(exception, "Path doesn't regular file or symlink");

		return false;
	}

	env->ReleaseStringUTFChars(path, temp);

	/* TODO: release */

	return true;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring path) {
	return Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2Lorg_kl_state_OverrideMode_2(env, clazz, path, take_default_mode(env));
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseFiles__Lorg_kl_state_OverrideMode_2_3Ljava_lang_String_2(JNIEnv* env, jclass clazz, jobject mode_object, jobjectArray paths) {
	/* TODO: release */

	return true;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseFiles___3Ljava_lang_String_2(JNIEnv* env, jclass clazz, jobjectArray paths) {
	return Java_org_kl_erase_EraseFS_eraseFiles__Lorg_kl_state_OverrideMode_2_3Ljava_lang_String_2(env, clazz, take_default_mode(env), paths);
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseDirectory__Ljava_lang_String_2Lorg_kl_state_OverrideMode_2Z(JNIEnv* env, jclass clazz, jstring path, jobject mode_object, jboolean recursived) {
	const char* temp = env->GetStringUTFChars(path, nullptr);
	const auto& folder = fs::path(temp);

	kl::erase_content eraser;

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

	for (const auto& item: fs::directory_iterator(folder)) {
		const auto& entity = item.path();

		if (fs::exists(entity)) {
			if (fs::is_symlink(entity) || fs::is_regular_file(entity)) {
				std::cout << " file regular | symlink : " << entity << std::endl;

				if (!eraser.check_permision(entity, fs::status(entity).permissions())) {
					std::cerr << "file hasn't enough permision: " << entity << std::endl;
				}
			} else {
				std::cerr << "file unknown type: " << entity << std::endl;
			}
		} else {
			std::cerr << "file doesn't exist: " << entity << std::endl;
		}
	}

	env->ReleaseStringUTFChars(path, temp);

	return true;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseDirectory__Ljava_lang_String_2Z(JNIEnv* env, jclass clazz, jstring path, jboolean recursived) {
	return Java_org_kl_erase_EraseFS_eraseDirectory__Ljava_lang_String_2Lorg_kl_state_OverrideMode_2Z(env, clazz, path, take_default_mode(env), recursived);
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

	if (temp == "DOE_MODE") {
		mode = kl::overwrite_mode::DOE_MODE;
	} else if (temp == "OPENBSD_MODE") {
		mode = kl::overwrite_mode::OPENBSD_MODE;
	} else if (temp == "DOD_MODE") {
		mode = kl::overwrite_mode::DOD_MODE;
	} else if (temp == "GUTMAN_MODE") {
		mode = kl::overwrite_mode::GUTMAN_MODE;
	} else {
		mode = kl::overwrite_mode::SIMPLE_MODE;
	}

	std::cout << "mode: " << temp << std::endl;

	env->ReleaseStringUTFChars(name, temp);

	return mode;
}







