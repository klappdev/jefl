#ifndef JNI_ERASE_ERASE_CONTENT_HPP_
#define JNI_ERASE_ERASE_CONTENT_HPP_

#include <filesystem>
#include <iostream>

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

		SETTER_OBJ_CLR(erase_entry, entry);
		SETTER_OBJ_RR(erase_entry, entry);
		GETTER_OBJ_LR(erase_entry, entry);

	private:
		erase_entry entry;
	};
}

#endif /* JNI_ERASE_ERASE_CONTENT_HPP_ */
