#include <iostream>
#include <filesystem>

#include "org_kl_erase_EraseFS.h"

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring path) {
	std::cout << "call jni method " << __func__ << std::endl;

	return false;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseFile__Ljava_lang_String_2Lorg_kl_state_OverrideMode_2(JNIEnv* env, jclass clazz, jstring path, jobject mode_object) {
	std::cout << "call jni method " << __func__ << std::endl;

	jclass override_mode_class = env->GetObjectClass(mode_object);

	jmethodID name_id = env->GetMethodID(override_mode_class, "name", "()Ljava/lang/String;");
	jstring name = (jstring) env->CallObjectMethod(mode_object, name_id);

	const char* temp = env->GetStringUTFChars(name, nullptr);

	if (temp == "SIMPLE_MODE") {
		std::cout << "mode: " << temp << std::endl;

	} else if (temp == "DOE_MODE") {
		std::cout << "mode: " << temp << std::endl;

	} else if (temp == "OPENBSD_MODE") {
		std::cout << "mode: " << temp << std::endl;

	} else if (temp == "DOD_MODE") {
		std::cout << "mode: " << temp << std::endl;

	} else if (temp == "GUTMAN_MODE") {
		std::cout << "mode: " << temp << std::endl;

	} else {
		std::cout << "mode: " << temp << std::endl;
	}

	env->ReleaseStringUTFChars(name, temp);

	return false;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseFiles___3Ljava_lang_String_2(JNIEnv* env, jclass clazz, jobjectArray paths) {
	std::cout << "call jni method " << __func__ << std::endl;

	return false;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseFiles__Lorg_kl_state_OverrideMode_2_3Ljava_lang_String_2(JNIEnv* env, jclass clazz, jobject mode_object, jobjectArray paths) {
	std::cout << "call jni method " << __func__ << std::endl;

	return false;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseDirectory__Ljava_lang_String_2Z(JNIEnv* env, jclass clazz, jstring paths, jboolean recursived) {
	std::cout << "call jni method " << __func__ << std::endl;

	return false;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_org_kl_erase_EraseFS_eraseDirectory__Ljava_lang_String_2Lorg_kl_state_OverrideMode_2Z(JNIEnv* env, jclass clazz, jstring paths, jobject mode_object, jboolean recursived) {
	std::cout << "call jni method " << __func__ << std::endl;

	return false;
}





