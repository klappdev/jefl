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

#pragma once

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

#include "EraseEntry.hpp"
#include "FileUtil.hpp"

namespace jefl {

	class FileEraser {
	public:
		FileEraser() = default;
		~FileEraser() = default;

		bool checkPermision(const fs::path& entry, fs::perms permision);

		bool init(const fs::path& entry, OverwriteMode mode);
		void reset();

		bool removeFile(const fs::path& file);

		bool overwriteFile();

		void setEntry(const EraseEntry& entry) { this->entry = entry; }
		const EraseEntry& getEntry() const { return entry; }

	private:
		bool overwriteByte(const int pass,  const uint8_t byte);
		bool overwriteBytes(const int pass, const char* mask);
		bool overwriteRandom(const int pass);
		bool overwriteData(const int pass);

		size_t initBuffer(const char* mask, const size_t length);
		size_t writeBuffer(const size_t count, const size_t tail);

		void showPermision(fs::perms permision);
		std::string randomText(size_t length);

	private:
		std::unique_ptr<uint8_t[]> buffer;
		FileUniquePtr file;

		EraseEntry entry;
	};
}
