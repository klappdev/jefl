#include "erase_content.hpp"

kl::erase_content::erase_content() {}
kl::erase_content::~erase_content() {}

bool kl::erase_content::check_permision(const fs::path& entity, fs::perms permision) {
	show_permision(permision);

	try {
		fs::permissions(entity,
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
