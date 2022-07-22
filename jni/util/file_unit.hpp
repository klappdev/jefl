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

#ifndef JNI_ERASE_FILE_UNIT_HPP_
#define JNI_ERASE_FILE_UNIT_HPP_

namespace kl::file_literals {
	inline constexpr unsigned long long int operator""_kB(unsigned long long int value) {
		return 1024u * value;
	}

	inline constexpr unsigned long long int operator""_MB(unsigned long long int value) {
		return 1024u * 1024u * value;
	}

	inline constexpr unsigned long long int operator""_GB(unsigned long long int value) {
		return 1024u * 1024u * 1024u * value;
	}

	inline constexpr unsigned long long int operator""_TB(unsigned long long int value) {
		return 1024u * 1024u * 1024u * 1024u * value;
	}
}

#endif /* JNI_ERASE_FILE_UNIT_HPP_ */
