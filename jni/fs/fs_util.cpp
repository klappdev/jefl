#include "fs_util.hpp"


kl::fs_util::fs_util() {}
kl::fs_util::~fs_util() {}

std::size_t kl::fs_util::block_size(const std::string& path) {
	std::size_t size;

#if !defined(_MSC_VER)
	struct stat file_info;

	if (lstat(path.c_str(), &file_info) < 0) {
		return 0;
	}

	size = file_info.st_blksize;
#else
	size = 4096;
#endif

	return size > 16 ? size : 512;
}

std::size_t kl::fs_util::count_hard_link(const std::string& path) {
	std::size_t count;

#ifdef _MSC_VER
	BY_HANDLE_FILE_INFORMATION file_info;
	HANDLE handle = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr,
			                   OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (handle == INVALID_HANDLE_VALUE) {
		return 0;
	}

	if (GetFileInformationByHandle(handle, &file_info)) {
		count = handle.nNumberOfLinks;
	}

	CloseHandle(handle);
#else
	struct stat file_info;

	if (lstat(path.c_str(), &file_info) < 0) {
		return 0;
	}

	count = file_info.st_nlink;
#endif

	return count;
}
