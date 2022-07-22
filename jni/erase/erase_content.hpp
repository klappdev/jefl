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

#ifndef JNI_ERASE_ERASE_CONTENT_HPP_
#define JNI_ERASE_ERASE_CONTENT_HPP_

#include <iostream>

#include <memory>
#include <cstring>
#include <random>

#if __has_include(<filesystem>)
# include <filesystem>
  namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
# include <experimental/filesystem>
  namespace fs = std::experimental::filesystem;
#else
# error "missing <filesystem>"
#endif

#include <property/property.hpp>

#include "../bean/erase_entry.hpp"
#include "../util/file_unit.hpp"
#include "../util/fs_util.hpp"
#include "../util/log_util.hpp"

using kl::file_literals::operator ""_kB;
using kl::file_literals::operator ""_MB;
using kl::file_literals::operator ""_GB;

namespace kl {

	class erase_content {
	public:
		erase_content();
		~erase_content();

		bool check_permision(const fs::path& entry, fs::perms permision);
		void show_permision(fs::perms permision);

		bool init_erase_etry(const fs::path& entry, kl::overwrite_mode mode);
		void reset_erase_etry();

		bool remove(const fs::path& file);

		bool overwrite();

		SETTER_OBJ_CLR(erase_entry, entry);
		GETTER_OBJ_LR(erase_entry, entry);

	private:
		bool overwrite_byte(const int pass,  const uint8_t byte);
		bool overwrite_bytes(const int pass, const char* mask);
		bool overwrite_random(const int pass);
		bool overwrite_data(const int pass);

		size_t init_buffer(const char* mask, const size_t length);
		size_t write_buffer(const size_t count, const size_t tail);

		std::string random_text(size_t length);

		std::unique_ptr<uint8_t[]> buffer;
		kl::file_unique_ptr file;

		erase_entry entry;
	};
}

#endif /* JNI_ERASE_ERASE_CONTENT_HPP_ */
