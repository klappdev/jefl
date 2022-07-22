/*
	Copyright (c) 2019 - 2022 https://github.com/klappdev

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
 */

#ifndef JNI_UTIL_LOG_UTIL_HPP_
#define JNI_UTIL_LOG_UTIL_HPP_

#include <iostream>

#define __DEBUG__ 0

namespace kl {
	class log_util final {
	public:
		log_util() = default;
		~log_util() = default;

		template<typename... Args>
		inline static void debug(Args&&... args) {
#if __DEBUG__ != 0
			(std::cout << ... << args) << '\n';
#endif
		}

		template<typename... Args>
		inline static void error(Args&&... args) {
#if __DEBUG__ != 0
			(std::cerr << ... << args) << '\n';
#endif
		}

		template<typename... Args>
		inline static void log(Args&&... args) {
#if __DEBUG__ != 0
			(std::clog << ... << args) << '\n';
#endif
		}

		template<typename... Args>
		inline static void scan(Args&&... args) {
#if __DEBUG__ != 0
			(std::cin >> ... >> args);
#endif
		}
	};
}

#endif /* JNI_UTIL_LOG_UTIL_HPP_ */
