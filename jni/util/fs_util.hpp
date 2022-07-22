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

#ifndef JNI_UTIL_FS_UTIL_HPP_
#define JNI_UTIL_FS_UTIL_HPP_

#include <iostream>
#include <string>
#include <memory>

#ifdef _MSC_VER
#	include <windows.h>
#else
#	include <sys/stat.h>
#	include <sys/types.h>
#endif

#include "log_util.hpp"

namespace kl {
#if defined(_MSC_VER)
	struct handle_deleter {
		void operator()(HANDLE handle) const {
			if (handle != INVALID_HANDLE_VALUE) {
				CloseHandle(handle);
			}
		}
	};

	using handle_unique_ptr = std::unique_ptr<void, handle_deleter>;
#endif
	struct file_deleter {
		void operator()(FILE* fd) {
			if (fd != nullptr) {
				kl::log_util::debug("close file ", fd);

				fclose(fd);
			}
		}
	};

	using file_unique_ptr = std::unique_ptr<FILE, file_deleter>;

	class fs_util final {
	public:
		fs_util();
		~fs_util();

		static std::size_t block_size(const std::string& path);
		static std::size_t count_hard_link(const std::string& path);

		static kl::file_unique_ptr make_open_file(const std::string& path, const std::string& mode);
#if defined(_MSC_VER)
		static kl::handle_unique_ptr make_open_handle(HANDLE handle);
#endif
	};
}

#endif /* JNI_UTIL_FS_UTIL_HPP_ */
