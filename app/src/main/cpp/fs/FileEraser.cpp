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

#include "FileEraser.hpp"

#include "FileUnit.hpp"
#include "../logging/Logging.hpp"

namespace jefl {

	using file_literals::operator ""_kB;
	using file_literals::operator ""_MB;
	using file_literals::operator ""_GB;

	bool FileEraser::checkPermision(const fs::path& entry, fs::perms permision) {
		showPermision(permision);

		try {
			fs::permissions(entry,
							fs::perms::owner_read | fs::perms::owner_write,
							fs::perm_options::add);
			return true;
		} catch (fs::filesystem_error& e) {
			return false;
		}
	}

	void FileEraser::showPermision(fs::perms permission) {
		log::info("owner permission: %s-%s-%s\n",
			  ((permission & std::filesystem::perms::owner_read) != std::filesystem::perms::none ? "r" : "-"),
			  ((permission & std::filesystem::perms::owner_write) != std::filesystem::perms::none ? "w" : "-"),
			  ((permission & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ? "x" : "-"));

		log::info("group permission: %s-%s-%s\n",
			  ((permission & std::filesystem::perms::group_read) != std::filesystem::perms::none ? "r" : "-"),
			  ((permission & std::filesystem::perms::group_write) != std::filesystem::perms::none ? "w" : "-"),
			  ((permission & std::filesystem::perms::group_exec) != std::filesystem::perms::none ? "x" : "-"));

		log::info("other permission: %s-%s-%s\n",
			  ((permission & std::filesystem::perms::others_read) != std::filesystem::perms::none ? "r" : "-"),
			  ((permission & std::filesystem::perms::others_write) != std::filesystem::perms::none ? "w" : "-"),
			  ((permission & std::filesystem::perms::others_exec) != std::filesystem::perms::none ? "x" : "-"));
	}

	bool FileEraser::init(const fs::path& file, OverwriteMode mode) {
		entry.fileName = file;
		entry.fileSize = fs::file_size(file);
		entry.bufferSize = blockSize(file);
		entry.mode = mode;

		if (entry.fileSize <= 0) {
			log::error("file size can't be negative: %ld\n", entry.fileSize);
			return false;
		}

		if (entry.fileSize > 2_GB) {
			log::error("file size can't be more 2GB: %ld\n", entry.fileSize);
			return false;
		}

		if (entry.bufferSize <= 0) {
			log::error("buffer size can't be negative: %d\n", entry.bufferSize);
			return false;
		}

		if (fs::hard_link_count(file) > 1) {
			log::error("count hard link must be one\n");
			return false;
		}

		return true;
	}

	void FileEraser::reset() {
		entry.fileName = "";
		entry.fileSize = 0_kB;
		entry.bufferSize = 0;
		entry.mode = OverwriteMode::SIMPLE_MODE;
	}

	bool FileEraser::removeFile(const fs::path& file) {
		std::string parent_path = file.parent_path();
		std::string fileName   = file.filename();
		fs::path copyFile = file;

		fileName = randomText(fileName.size());

		log::info("file name: %s\n", fileName.c_str());

		copyFile.replace_filename(fs::path(fileName));

		try {
			fs::rename(file, copyFile);
			fs::remove(copyFile);
		} catch (fs::filesystem_error& e) {
			return false;
		}

		return true;
	}

	bool FileEraser::overwriteFile() {
		switch (entry.mode) {
		case OverwriteMode::SIMPLE_MODE:
			if (!overwriteByte(1, 0x00)) { return false; }

			break;
		case OverwriteMode::DOE_MODE:
			if (!overwriteRandom(1)) { return false; }
			if (!overwriteRandom(2)) { return false; }
			if (!overwriteBytes(3, "DoE")) { return false; }

			break;
		case OverwriteMode::OPENBSD_MODE:
			if (!overwriteByte(1, 0xFF)) { return false; }
			if (!overwriteByte(2, 0x00)) { return false; }
			if (!overwriteByte(3, 0xFF)) { return false; }

			break;
		case OverwriteMode::RCMP_MODE:
			if (!overwriteByte(1, 0x00)) { return false; }
			if (!overwriteByte(2, 0xFF)) { return false; }
			if (!overwriteBytes(3, "RCMP")) { return false; }

			break;
		case OverwriteMode::DOD_MODE:
			if (!overwriteByte(1, 0xF6)) { return false; }
			if (!overwriteByte(2, 0x00)) { return false; }
			if (!overwriteByte(3, 0xFF)) { return false; }
			if (!overwriteRandom(4)) { return false; }
			if (!overwriteByte(5, 0x00)) { return false; }
			if (!overwriteByte(6, 0xFF)) { return false; }
			if (!overwriteRandom(7)) { return false; }

			break;
		case OverwriteMode::GUTMAN_MODE:
			if (!overwriteRandom(1)) { return false; }
			if (!overwriteRandom(2)) { return false; }
			if (!overwriteRandom(3)) { return false; }
			if (!overwriteRandom(4)) { return false; }
			if (!overwriteByte(5, 0x55)) { return false; }
			if (!overwriteByte(6, 0xAA)) { return false; }
			if (!overwriteBytes(7, "’I$")) { return false; }	/* 0x92, 0x49, 0x24 */
			if (!overwriteBytes(8, "I$’")) { return false; }	/* 0x49, 0x24, 0x92 */
			if (!overwriteBytes(9, "$’I")) { return false; }	/* 0x24, 0x92, 0x49 */
			if (!overwriteByte(10, 0x00)) { return false; }
			if (!overwriteByte(11, 0x11)) { return false; }
			if (!overwriteByte(12, 0x22)) { return false; }
			if (!overwriteByte(13, 0x33)) { return false; }
			if (!overwriteByte(14, 0x44)) { return false; }
			if (!overwriteByte(15, 0x55)) { return false; }
			if (!overwriteByte(16, 0x66)) { return false; }
			if (!overwriteByte(17, 0x77)) { return false; }
			if (!overwriteByte(18, 0x88)) { return false; }
			if (!overwriteByte(19, 0x99)) { return false; }
			if (!overwriteByte(20, 0xAA)) { return false; }
			if (!overwriteByte(21, 0xBB)) { return false; }
			if (!overwriteByte(22, 0xCC)) { return false; }
			if (!overwriteByte(23, 0xDD)) { return false; }
			if (!overwriteByte(24, 0xEE)) { return false; }
			if (!overwriteByte(25, 0xFF)) { return false; }
			if (!overwriteBytes(26, "’I$")) { return false; }	/* 0x92, 0x49, 0x24 */
			if (!overwriteBytes(27, "I$’")) { return false; }	/* 0x49, 0x24, 0x92 */
			if (!overwriteBytes(28, "$’I")) { return false; }	/* 0x24, 0x92, 0x49 */
			if (!overwriteBytes(29, "m¶Û")) { return false; }	/* 0x6D, 0xB6, 0xDB */
			if (!overwriteBytes(30, "¶Ûm")) { return false; }	/* 0xB6, 0xDB, 0x6D */
			if (!overwriteBytes(31, "Ûm¶")) { return false; }	/* 0xDB, 0x6D, 0xB6 */
			if (!overwriteRandom(32)) { return false; }
			if (!overwriteRandom(33)) { return false; }
			if (!overwriteRandom(34)) { return false; }
			if (!overwriteRandom(35)) { return false; }
			if (!overwriteByte(36, 0x00)) { return false; }

			break;
		default:
			log::error("overwrite mode doesn't choose");
		}

		return true;
	}

	bool FileEraser::overwriteByte(const int pass, const uint8_t byte) {
		const auto& [fileName, fileSize, bufferSize, mode] = entry;

		this->buffer = std::make_unique<uint8_t[]>(bufferSize);
		std::memset(buffer.get(), byte, bufferSize);

	#if JEFL_DEBUG
		for (int i = 0; i < bufferSize; i++) {
			log::debug(" data[%d] = %u\n", std::uint32_t(buffer.get()[i]);
		}
	#endif

		this->file = makeOpenFile(fileName, "r+b");

		if (!overwriteData(pass)) {
			return false;
		}

		return true;
	}

	bool FileEraser::overwriteBytes(const int pass, const char* mask) {
		const auto& [fileName, fileSize, bufferSize, mode] = entry;

		this->buffer = std::make_unique<uint8_t[]>(bufferSize);
		initBuffer(mask, std::strlen(mask));

	#if JEFL_DEBUG
		for (int i = 0; i < bufferSize; i++) {
			log::debug(" data[%d] = %u\n", std::uint32_t(buffer.get()[i]);
		}
	#endif

		this->file = makeOpenFile(fileName, "r+b");

		if (!overwriteData(pass)) {
			return false;
		}

		return true;
	}

	bool FileEraser::overwriteRandom(const int pass) {
		const auto& [fileName, fileSize, bufferSize, mode] = entry;

		std::string random_data = randomText(bufferSize);
		buffer = std::make_unique<uint8_t[]>(bufferSize);

		std::copy(random_data.begin(), random_data.end(), buffer.get());

	#if JEFL_DEBUG
		for (int i = 0; i < bufferSize; i++) {
			log::debug(" data[%d] = %u\n", std::uint32_t(buffer.get()[i]);
		}
	#endif

		this->file = makeOpenFile(fileName, "r+b");

		if (!overwriteData(pass)) {
			return false;
		}

		return true;
	}

	bool FileEraser::overwriteData(const int pass) {
		const auto& [fileName, fileSize, bufferSize, mode] = entry;

		const size_t count = fileSize / bufferSize;
		const size_t tail  = fileSize % bufferSize;

		size_t writted = 0;

		log::debug("buffer size   : %d\n", bufferSize);
		log::debug("file   size   : %ld\n", fileSize);
		log::debug("buffer count  : %ld\n", count);
		log::debug("buffer tail   : %lu\n", tail);
		log::debug("overwrite pass: %u\n", pass);

		if (fseek(file.get(), 0, SEEK_SET) != 0) {
			log::error("couldn't seek in file\n");

			return false;
		}

		writted = writeBuffer(count, tail);

		if (writted != fileSize) {
			log::error("couldn't write buffer in file\n");

			return false;
		}

		fflush(file.get());

		if (fseek(file.get(), 0, SEEK_SET) != 0) {
			log::error("couldn't seek in file\n");

			return false;
		}

		file.reset();

		return true;
	}

	size_t FileEraser::writeBuffer(const size_t count, const size_t tail) {
		const auto& [fileName, fileSize, bufferSize, mode] = entry;
		size_t writted = 0;

		if (count == 0) {
			writted = std::fwrite(buffer.get(), 1, tail, file.get());

			log::info("writted: %lu - %lu\n", writted, tail);
		} else {
			for (uint32_t i = 0; i < count; i++) {
				writted += std::fwrite(buffer.get(), 1, bufferSize, file.get());
			}

			writted += std::fwrite(buffer.get(), 1, tail, file.get());

			log::info("writted: %lu - %lu\n", writted, fileSize);
		}

		return writted;
	}

	size_t FileEraser::initBuffer(const char* mask, const size_t length) {
		uint8_t* data = buffer.get();
		size_t   size = entry.bufferSize;
		uint32_t i = 0;

		while (size > 0) {
			*data++ = mask[i];

			if (++i == length) {
				i = 0;
			}

			--size;
		}

		return length;
	}

	std::string FileEraser::randomText(size_t length) {
		auto& sequence = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		std::string result;

		std::mt19937 range {std::random_device{}()};
		std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(sequence) - 2);

		result.reserve(length);

		while (length--) {
			result += sequence[pick(range)];
		}

		return result;
	}
}
