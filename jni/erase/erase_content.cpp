#include "erase_content.hpp"

kl::erase_content::erase_content() {}
kl::erase_content::~erase_content() {}

bool kl::erase_content::check_permision(const fs::path& entry, fs::perms permision) {
	show_permision(permision);

	try {
		fs::permissions(entry,
						fs::perms::owner_read | fs::perms::owner_write,
						fs::perm_options::add);
		return true;
	} catch (fs::filesystem_error& e) {
		return false;
	}
}

void kl::erase_content::show_permision(fs::perms permision) {
    std::cout << ((permision & fs::perms::owner_read)  != fs::perms::none ? "r" : "-")
              << ((permision & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
              << ((permision & fs::perms::owner_exec)  != fs::perms::none ? "x" : "-")
              << ((permision & fs::perms::group_read)  != fs::perms::none ? "r" : "-")
              << ((permision & fs::perms::group_write) != fs::perms::none ? "w" : "-")
              << ((permision & fs::perms::group_exec)  != fs::perms::none ? "x" : "-")
              << ((permision & fs::perms::others_read) != fs::perms::none ? "r" : "-")
              << ((permision & fs::perms::others_write) != fs::perms::none ? "w" : "-")
              << ((permision & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
              << std::endl;
}

bool kl::erase_content::init_erase_etry(const fs::path& file, kl::overwrite_mode mode) {
	entry.set_file_name(file);
	entry.set_file_size(fs::file_size(file));
	entry.set_buffer_size(kl::fs_util::block_size(file));
	/* entry.set_buffer(""); */
	entry.set_mode(mode);

	if (entry.get_file_size() <= 0) {
		std::cerr << "file size can't be negative: " << entry.get_file_size() << std::endl;
		return false;
	}

	if (entry.get_file_size() > 2_GB) {
		std::cerr << "file size can't be more 2GB: " << entry.get_file_size() << std::endl;
		return false;
	}

	if (entry.get_buffer_size() <= 0) {
		std::cerr << "buffer size can't be negative: " << entry.get_buffer_size() << std::endl;
		return false;
	}

	if (fs::hard_link_count(file) > 1) {
		std::cerr << "count hard link must be one " << std::endl;
		return false;
	}

	return true;
}

void kl::erase_content::reset_erase_etry() {
	entry.set_file_name("");
	entry.set_file_size(0_kB);
	entry.set_buffer_size(0);
	/* entry.set_buffer(""); */
	entry.set_mode(kl::overwrite_mode::SIMPLE_MODE);
}

