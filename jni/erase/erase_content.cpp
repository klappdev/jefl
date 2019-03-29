#include "erase_content.hpp"

#define __DEBUG__ 0

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

	file_name = random_text(file_name.size());

#if __DEBUG__
	std::cout << "file name: "  << file_name	<< std::endl;
#endif

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
		if (!overwrite_byte(1, 0x00)) { return false; }

		break;
	case kl::overwrite_mode::DOE_MODE:
		if (!overwrite_random(1)) { return false; }
		if (!overwrite_random(2)) { return false; }
		if (!overwrite_bytes(3, "DoE")) { return false; }

		break;
	case kl::overwrite_mode::OPENBSD_MODE:
		if (!overwrite_byte(1, 0xFF)) { return false; }
		if (!overwrite_byte(2, 0x00)) { return false; }
		if (!overwrite_byte(3, 0xFF)) { return false; }

		break;
	case kl::overwrite_mode::RCMP_MODE:
		if (!overwrite_byte(1, 0x00)) { return false; }
		if (!overwrite_byte(2, 0xFF)) { return false; }
		if (!overwrite_bytes(3, "RCMP")) { return false; }

		break;
	case kl::overwrite_mode::DOD_MODE:
		if (!overwrite_byte(1, 0xF6)) { return false; }
		if (!overwrite_byte(2, 0x00)) { return false; }
		if (!overwrite_byte(3, 0xFF)) { return false; }
		if (!overwrite_random(4)) { return false; }
		if (!overwrite_byte(5, 0x00)) { return false; }
		if (!overwrite_byte(6, 0xFF)) { return false; }
		if (!overwrite_random(7)) { return false; }

		break;
	case kl::overwrite_mode::GUTMAN_MODE:
		if (!overwrite_random(1)) { return false; }
		if (!overwrite_random(2)) { return false; }
		if (!overwrite_random(3)) { return false; }
		if (!overwrite_random(4)) { return false; }
		if (!overwrite_byte(5, 0x55)) { return false; }
		if (!overwrite_byte(6, 0xAA)) { return false; }
		if (!overwrite_bytes(7, "’I$")) { return false; }	/* 0x92, 0x49, 0x24 */
		if (!overwrite_bytes(8, "I$’")) { return false; }	/* 0x49, 0x24, 0x92 */
		if (!overwrite_bytes(9, "$’I")) { return false; }	/* 0x24, 0x92, 0x49 */
		if (!overwrite_byte(10, 0x00)) { return false; }
		if (!overwrite_byte(11, 0x11)) { return false; }
		if (!overwrite_byte(12, 0x22)) { return false; }
		if (!overwrite_byte(13, 0x33)) { return false; }
		if (!overwrite_byte(14, 0x44)) { return false; }
		if (!overwrite_byte(15, 0x55)) { return false; }
		if (!overwrite_byte(16, 0x66)) { return false; }
		if (!overwrite_byte(17, 0x77)) { return false; }
		if (!overwrite_byte(18, 0x88)) { return false; }
		if (!overwrite_byte(19, 0x99)) { return false; }
		if (!overwrite_byte(20, 0xAA)) { return false; }
		if (!overwrite_byte(21, 0xBB)) { return false; }
		if (!overwrite_byte(22, 0xCC)) { return false; }
		if (!overwrite_byte(23, 0xDD)) { return false; }
		if (!overwrite_byte(24, 0xEE)) { return false; }
		if (!overwrite_byte(25, 0xFF)) { return false; }
		if (!overwrite_bytes(26, "’I$")) { return false; }	/* 0x92, 0x49, 0x24 */
		if (!overwrite_bytes(27, "I$’")) { return false; }	/* 0x49, 0x24, 0x92 */
		if (!overwrite_bytes(28, "$’I")) { return false; }	/* 0x24, 0x92, 0x49 */
		if (!overwrite_bytes(29, "m¶Û")) { return false; }	/* 0x6D, 0xB6, 0xDB */
		if (!overwrite_bytes(30, "¶Ûm")) { return false; }	/* 0xB6, 0xDB, 0x6D */
		if (!overwrite_bytes(31, "Ûm¶")) { return false; }	/* 0xDB, 0x6D, 0xB6 */
		if (!overwrite_random(32)) { return false; }
		if (!overwrite_random(33)) { return false; }
		if (!overwrite_random(34)) { return false; }
		if (!overwrite_random(35)) { return false; }
		if (!overwrite_byte(36, 0x00)) { return false; }

		break;
	default:
		std::cerr << "overwrite mode doesn't choose" << std::endl;
	}

	return true;
}

bool kl::erase_content::overwrite_byte(const int pass, const uint8_t byte) {
	const uint32_t size = entry.get_buffer_size();

	this->buffer = std::make_unique<uint8_t[]>(size);
	std::memset(buffer.get(), byte, size);

#if __DEBUG__
	for (int i = 0; i < size; i++) {
		std::cout << " data[" << i << "] = "  << uint32_t(buffer.get()[i]);
	}
#endif

	this->file = kl::fs_util::make_open_file(entry.get_file_name(), "r+b");

	if (!overwrite_data(pass)) {
		return false;
	}

	return true;
}

bool kl::erase_content::overwrite_bytes(const int pass, const char* mask) {
	const uint32_t size = entry.get_buffer_size();

	this->buffer = std::make_unique<uint8_t[]>(size);
	init_buffer(mask, std::strlen(mask));

#if __DEBUG__
	for (int i = 0; i < size; i++) {
		std::cout << " data[" << i << "] = "  << uint32_t(buffer.get()[i]);
	}
#endif

	this->file = kl::fs_util::make_open_file(entry.get_file_name(), "r+b");

	if (!overwrite_data(pass)) {
		return false;
	}

	return true;
}

bool kl::erase_content::overwrite_random(const int pass) {
	const uint32_t size = entry.get_buffer_size();

	std::string random_data = random_text(size);
	buffer = std::make_unique<uint8_t[]>(size);

	std::copy(random_data.begin(), random_data.end(), buffer.get());

#if __DEBUG__
	for (int i = 0; i < size; i++) {
		std::cout << " data[" << i << "] = "  << uint32_t(buffer.get()[i]);
	}
#endif

	this->file = kl::fs_util::make_open_file(entry.get_file_name(), "r+b");

	if (!overwrite_data(pass)) {
		return false;
	}

	return true;
}

bool kl::erase_content::overwrite_data(const int pass) {
	const uint32_t buffer_size = entry.get_buffer_size();
	const uintmax_t file_size  = entry.get_file_size();

	const size_t count = file_size / buffer_size;
	const size_t tail  = file_size % buffer_size;

	ssize_t writted = 0;

#if __DEBUG__
	std::cerr << "buffer size 	: " << buffer_size 	<< std::endl;
	std::cerr << "file   size 	: " << file_size 	<< std::endl;
	std::cerr << "buffer count	: " << count 		<< std::endl;
	std::cerr << "buffer tail 	: " << tail 		<< std::endl;
	std::cout << "overwrite pass: " << pass 		<< std::endl;
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

size_t kl::erase_content::write_buffer(const size_t count, const size_t tail) {
	size_t writted = 0;

	if (count == 0) {
		writted = std::fwrite(buffer.get(), 1, tail, file.get());
#if __DEBUG__
		std::cerr << "writted: " << writted << " - " << tail << std::endl;
#endif
	} else {
		for (int i = 0; i < count; i++) {
			writted += std::fwrite(buffer.get(), 1, entry.get_buffer_size(), file.get());
		}

		writted += std::fwrite(buffer.get(), 1, tail, file.get());
#if __DEBUG__
		std::cerr << "writted: " << writted << " - " << entry.get_file_size() << std::endl;
#endif
	}

	return writted;
}

size_t kl::erase_content::init_buffer(const char* mask, const size_t length) {
	uint8_t* data = buffer.get();
	size_t   size = entry.get_buffer_size();
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

std::string kl::erase_content::random_text(size_t length) {
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
