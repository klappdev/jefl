#ifndef JNI_ERASE_ERASE_CONTENT_HPP_
#define JNI_ERASE_ERASE_CONTENT_HPP_

#include <filesystem>
#include <iostream>

#include <memory>
#include <cstring>
#include <random>

#include <property/property.hpp>

#include "../bean/erase_entry.hpp"
#include "../fs/fs_util.hpp"
#include "../fs/file_unit.hpp"

namespace fs = std::filesystem;

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
