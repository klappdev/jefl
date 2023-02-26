/*
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2019-2023 https://github.com/klappdev
 *
 * Permission is hereby  granted, free of charge, to any  person obtaining a copy
 * of this software and associated  documentation files (the "Software"), to deal
 * in the Software  without restriction, including without  limitation the rights
 * to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
 * copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
 * IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
 * FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
 * AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
 * LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <jni.h>

#include "FileEraser.hpp"
#include "OverwriteMode.hpp"

namespace {
	constexpr jint JNI_VERSION = JNI_VERSION_1_8;
	jclass eraseExceptionClass = nullptr;
	jclass overwriteModeClass = nullptr;

	jfieldID simpleModeFieldId = nullptr;
	jmethodID nameMethodId = nullptr;
}

namespace jefl {

	jboolean nativeEraseFile(JNIEnv* env, jclass clazz, jstring jvmPath, jobject jvmOverwriteMode) {
		const char* rawPath = env->GetStringUTFChars(jvmPath, nullptr);
		const auto& filePath = fs::path(rawPath);

		jefl::FileEraser eraser;

		jstring jvmModeName = (jstring) env->CallObjectMethod(jvmOverwriteMode, nameMethodId);
		const char* rawModeName = env->GetStringUTFChars(jvmModeName, nullptr);
		auto overwriteMode = OVERWRITE_MODE.value(rawModeName);

		if (!overwriteMode.has_value()) {
			env->ThrowNew(eraseExceptionClass, "Set unknown OverwriteMode");
			env->ReleaseStringUTFChars(jvmPath, rawPath);
			env->ReleaseStringUTFChars(jvmModeName, rawModeName);

			return false;
		}

		if (!eraser.init(filePath, *overwriteMode)) {
			env->ThrowNew(eraseExceptionClass, "Init eraser was failed");
			env->ReleaseStringUTFChars(jvmPath, rawPath);
			env->ReleaseStringUTFChars(jvmModeName, rawModeName);

			return false;
		}

		if (!fs::exists(filePath)) {
			env->ThrowNew(eraseExceptionClass, "File doesn't exist");
			env->ReleaseStringUTFChars(jvmPath, rawPath);
			env->ReleaseStringUTFChars(jvmModeName, rawModeName);

			return false;
		}

		if (!fs::is_regular_file(filePath)) {
			env->ThrowNew(eraseExceptionClass, "Path doesn't regular file or symlink");
			env->ReleaseStringUTFChars(jvmPath, rawPath);
			env->ReleaseStringUTFChars(jvmModeName, rawModeName);

			return false;
		}

		if (!eraser.checkPermision(filePath, fs::status(filePath).permissions())) {
			env->ThrowNew(eraseExceptionClass, "File hasn't enough permision (maybe not user)");
			env->ReleaseStringUTFChars(jvmPath, rawPath);
			env->ReleaseStringUTFChars(jvmModeName, rawModeName);

			return false;
		}

		if (!eraser.overwriteFile()) {
			env->ThrowNew(eraseExceptionClass, "overwrite entry fail");
			env->ReleaseStringUTFChars(jvmPath, rawPath);
			env->ReleaseStringUTFChars(jvmModeName, rawModeName);

			return false;
		}

		try {
			fs::resize_file(filePath, 0);
		} catch (fs::filesystem_error& e) {
			env->ThrowNew(eraseExceptionClass, "truncate file fail");
			env->ReleaseStringUTFChars(jvmPath, rawPath);
			env->ReleaseStringUTFChars(jvmModeName, rawModeName);

			return false;
		}

		if (!eraser.removeFile(filePath)) {
			env->ThrowNew(eraseExceptionClass, "change name fail");
			env->ReleaseStringUTFChars(jvmPath, rawPath);
			env->ReleaseStringUTFChars(jvmModeName, rawModeName);

			return false;
		}

		env->ReleaseStringUTFChars(jvmPath, rawPath);
		env->ReleaseStringUTFChars(jvmModeName, rawModeName);

		return true;
	}

	jboolean nativeEraseFileWithDefaultMode(JNIEnv* env, jclass clazz, jstring jvmPath) {
		jobject simpleModeObject = env->GetStaticObjectField(overwriteModeClass, simpleModeFieldId);

		return nativeEraseFile(env, clazz, jvmPath, simpleModeObject);
	}

	jboolean nativeEraseFiles(JNIEnv* env, jclass clazz, jobjectArray jvmPaths, jobject jvmOverwriteMode) {
		size_t length = env->GetArrayLength(jvmPaths);

		for (int i = 0; i < length; i++) {
			jstring jvmPath = (jstring) env->GetObjectArrayElement(jvmPaths, i);

			if (!nativeEraseFile(env, clazz, jvmPath, jvmOverwriteMode)) {
				return false;
			}
		}

		return true;
	}

	jboolean nativeEraseFilesWithDefaultMode(JNIEnv* env, jclass clazz, jobjectArray jvmPaths) {
		jobject simpleModeObject = env->GetStaticObjectField(overwriteModeClass, simpleModeFieldId);

		return nativeEraseFiles(env, clazz, jvmPaths, simpleModeObject);
	}

	jboolean nativeEraseDirectory(JNIEnv* env, jclass clazz, jstring jvmPath, jobject jvmOverwriteMode, jboolean jvmRecursived) {
		const char* rawPath = env->GetStringUTFChars(jvmPath, nullptr);
		const auto& folder = fs::path(rawPath);
		jstring file_path = nullptr;

		if (!fs::exists(folder)) {
			env->ThrowNew(eraseExceptionClass, "Directory doesn't exist");

			return false;
		}

		if (!fs::is_directory(folder)) {
			env->ThrowNew(eraseExceptionClass, "Path doesn't directory");

			return false;
		}

		if (jvmRecursived) {
			for (const auto& item : fs::recursive_directory_iterator(folder)) {
				file_path = env->NewStringUTF(item.path().c_str());

				if (!fs::is_directory(item.path())) {
					if (!nativeEraseFile(env, clazz, file_path, jvmOverwriteMode)) {
						env->ReleaseStringUTFChars(jvmPath, rawPath);
						return false;
					}
				}
			}
		} else {
			for (const auto& item : fs::directory_iterator(folder)) {
				file_path = env->NewStringUTF(item.path().c_str());

				if (!nativeEraseFile(env, clazz, file_path, jvmOverwriteMode)) {
					env->ReleaseStringUTFChars(jvmPath, rawPath);
					return false;
				}
			}
		}

		env->ReleaseStringUTFChars(jvmPath, rawPath);

		return true;
	}

	jboolean nativeEraseDirectoryWithDefaultMode(JNIEnv* env, jclass clazz, jstring jvmPath, jboolean jvmRecursived) {
		jobject simpleModeObject = env->GetStaticObjectField(overwriteModeClass, simpleModeFieldId);

		return nativeEraseDirectory(env, clazz, jvmPath, simpleModeObject, jvmRecursived);
	}

	const std::array<JNINativeMethod, 6> JNI_METHODS = {{
        {"eraseFile", "(Ljava/lang/String;)Z", (void*)nativeEraseFileWithDefaultMode},
        {"eraseFile", "(Ljava/lang/String;Lorg/kl/jefl/OverwriteMode;)Z", (void*)nativeEraseFile},
		{"eraseFiles", "([Ljava/lang/String;)Z", (void*)nativeEraseFilesWithDefaultMode},
		{"eraseFiles", "(Lorg/kl/jefl/OverwriteMode;[Ljava/lang/String;)Z", (void*)nativeEraseFiles},
        {"eraseDirectory", "(Ljava/lang/String;Z)Z", (void*)nativeEraseDirectoryWithDefaultMode},
        {"eraseDirectory", "(Ljava/lang/String;Lorg/kl/jefl/OverwriteMode;Z)Z", (void*)nativeEraseDirectory}
    }};
}

jint registerEraseManager(JNIEnv* env) {
	using jefl::JNI_METHODS;
	jclass temporaryClass = nullptr;

	temporaryClass = env->FindClass("org/kl/jefl/EraseException");
	eraseExceptionClass = (jclass) env->NewGlobalRef(temporaryClass);
	env->DeleteLocalRef(temporaryClass);

	temporaryClass = env->FindClass("org/kl/jefl/OverwriteMode");
	overwriteModeClass = (jclass) env->NewGlobalRef(temporaryClass);
	env->DeleteLocalRef(temporaryClass);

	simpleModeFieldId = env->GetStaticFieldID(overwriteModeClass, "SIMPLE_MODE", "Lorg/kl/jefl/OverwriteMode;");
	nameMethodId = env->GetMethodID(overwriteModeClass, "name", "()Ljava/lang/String;");

	jclass fileManagerClass = env->FindClass("org/kl/jefl/FileEraser");
	return env->RegisterNatives(fileManagerClass, JNI_METHODS.data(), JNI_METHODS.size());
}

void unregisterEraseManager(JNIEnv* env) {
	env->DeleteGlobalRef(overwriteModeClass);
	env->DeleteGlobalRef(eraseExceptionClass);
}

