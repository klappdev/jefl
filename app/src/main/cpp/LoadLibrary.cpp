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

#include "logging/Logging.hpp"

/*
extern int registerJniExceptions(JNIEnv*);
extern void unregisterJniExceptions(JNIEnv*);
*/
extern int registerEraseManager(JNIEnv*);
extern void unregisterEraseManager(JNIEnv*);

static constexpr jint JNI_DEFAULT_VERSION = JNI_VERSION_1_8;

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* jvm, void* reserved) {
	JNIEnv* env = nullptr;

	if (jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_DEFAULT_VERSION) != JNI_OK) {
		jefl::log::error("Load libjefl library with error: could not get JNIEnv*");
		return JNI_ERR;
	}

	/*
	registerJniExceptions(env);
	*/

	if (registerEraseManager(env) != 0) {
		jefl::log::error("Could not register erase manager");
		return JNI_ERR;
	}

	jefl::log::info("Load libjefl library successfully");

	return JNI_DEFAULT_VERSION;
}

extern "C" JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* jvm, void* reserved) {
	JNIEnv* env = nullptr;

	if (jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_DEFAULT_VERSION)) {
		jefl::log::error("Unload libjefl library with error: could not get JNIEnv*");
		return;
	}

	/*
	unregisterJniExceptions(env);
	 */
	unregisterEraseManager(env);

	jefl::log::info("Unload libjefl library successfully");
}
