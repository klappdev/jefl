#include <iostream>
#include <filesystem>

#include "org_kl_erase_EraseFS.h"
#include "state/overwrite_mode.hpp"

namespace fs = std::filesystem;

static jobject take_default_mode(JNIEnv *env);

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2Lorg_kl_state_OverrideMode_2(JNIEnv* env, jclass clazz, jstring path, jobject mode_object) {
	return false;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring path) {
	return Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2Lorg_kl_state_OverrideMode_2(env, clazz, path, take_default_mode(env));
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseFiles__Lorg_kl_state_OverrideMode_2_3Ljava_lang_String_2(JNIEnv* env, jclass clazz, jobject mode_object, jobjectArray paths) {
	return false;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseFiles___3Ljava_lang_String_2(JNIEnv* env, jclass clazz, jobjectArray paths) {
	return Java_org_kl_erase_EraseFS_eraseFiles__Lorg_kl_state_OverrideMode_2_3Ljava_lang_String_2(env, clazz, take_default_mode(env), paths);
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseDirectory__Ljava_lang_String_2Lorg_kl_state_OverrideMode_2Z(JNIEnv* env, jclass clazz, jstring path, jobject mode_object, jboolean recursived) {
	const char* temp = env->GetStringUTFChars(path, nullptr);

	for (auto& item: fs::directory_iterator(fs::path(temp))) {

		if (fs::exists(item.path())) {
			if (fs::is_symlink(item.path()) || fs::is_regular_file(item.path())) {
				std::cout << " file regular | symlink : " << item.path() << std::endl;

				/* show_permision(fs::status(item.path()).permissions()); */
			} else {
				std::cerr << " unknown file type: " << item.path() << std::endl;
			}
		} else {
			std::cerr << " file not exist: " << item.path() << std::endl;
		}
	}

	env->ReleaseStringUTFChars(path, temp);

	return false;
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







