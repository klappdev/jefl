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
	entry.set_mode(kl::overwrite_mode::SIMPLE_MODE);
}

bool kl::erase_content::remove(const fs::path& file) {
	std::string parent_path = file.parent_path();
	std::string file_name   = file.filename();
	fs::path copy_file = file;

	random_name(file_name, file_name.size());

	copy_file.replace_filename(fs::path(file_name));

	try {
		fs::rename(file, copy_file);
		fs::remove(copy_file);
	} catch (fs::filesystem_error& e) {
		return false;
	}

	return true;
}

bool kl::erase_content::overwrite() {
	switch (entry.get_mode()) {
	case kl::overwrite_mode::SIMPLE_MODE:
		if (!overwrite(1, 0x00)) {
			return false;
		}

		break;
	case kl::overwrite_mode::DOE_MODE:
		std::cerr << "DOE_MODE not implemented" << std::endl;

		break;
	case kl::overwrite_mode::OPENBSD_MODE:
		std::cerr << "OPENBSD_MODE not implemented" << std::endl;

		break;
	case kl::overwrite_mode::RCMP_MODE:
		std::cerr << "RCMP_MODE not implemented" << std::endl;

		break;
	case kl::overwrite_mode::DOD_MODE:
		std::cerr << "DOD_MODE not implemented" << std::endl;

		break;
	case kl::overwrite_mode::GUTMAN_MODE:
		std::cerr << "GUTMAN_MODE not implemented" << std::endl;

		break;
	default:
		std::cerr << "overwrite mode doesn't choose" << std::endl;
	}

	return true;
}

bool kl::erase_content::overwrite(const int pass, const int byte) {
	std::cout << "byte: " << byte << std::endl;

	const uint32_t size = entry.get_buffer_size();

	this->buffer = std::make_unique<uint8_t[]>(size);
	std::memset(buffer.get(), byte, size);

#if 0
	for (int i = 0; i < size; i++) {
		std::cout << " data[" << i << "] = "
				  << static_cast<uint32_t>(buffer.get()[i]);
	}
#endif

	this->file = kl::fs_util::make_open_file(entry.get_file_name(), "r+b");

	if (!overwrite(pass)) {
		return false;
	}

	return true;
}

bool kl::erase_content::overwrite(const int pass) {
	const uint32_t buffer_size = entry.get_buffer_size();
	const uintmax_t file_size  = entry.get_file_size();

	const size_t count = file_size / buffer_size;
	const size_t tail  = file_size % buffer_size;

	ssize_t writted = 0;

#if 0
	std::cerr << "buffer size : " << buffer_size << std::endl;
	std::cerr << "file   size : " << file_size << std::endl;
	std::cerr << "buffer count: " << count << std::endl;
	std::cerr << "buffer tail : " << tail << std::endl;
	std::cerr << "file pos    : " << ftell(file.get()) << std::endl;
#endif

	if (fseek(file.get(), 0, SEEK_SET) != 0) {
		std::cerr << "couldn't seek in file" << std::endl;

		return false;
	}

	writted = write_buffer(count, tail);

	if (writted != file_size) {
		std::cerr << "couldn't write buffer in file" << std::endl;

		return false;
	}

	fflush(file.get());

	if (fseek(file.get(), 0, SEEK_SET) != 0) {
		std::cerr << "couldn't seek in file" << std::endl;

		return false;
	}

	file.reset();

	return true;
}

ssize_t kl::erase_content::write_buffer(const size_t count, const size_t tail) {
	size_t writted = 0;

	if (count == 0) {
		writted = std::fwrite(buffer.get(), 1, tail, file.get());
#if 0
		std::cerr << "writted: " << writted << " - " << tail << std::endl;
#endif
	} else {
		for (int i = 0; i < count; i++) {
			writted += std::fwrite(buffer.get(), 1, entry.get_buffer_size(), file.get());
		}

		writted += std::fwrite(buffer.get(), 1, tail, file.get());
#if 0
		std::cerr << "writted: " << writted << " - " << entry.get_file_size() << std::endl;
#endif
	}

	return writted;
}

void kl::erase_content::random_name(std::string& file_name, size_t length) {
	auto& sequence = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string result;

	std::mt19937 range {std::random_device{}()};
	std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(sequence) - 2);

	std::cout << "file name: " << file_name << std::endl;

	result.reserve(length);

	while (length--) {
		result += sequence[pick(range)];
	}

	file_name = result;

	std::cout << "random name: " << file_name << std::endl;
}
