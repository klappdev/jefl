#ifndef JNI_FS_FS_UTIL_HPP_
#define JNI_FS_FS_UTIL_HPP_

#include <iostream>
#include <string>
#include <memory>

#ifdef _MSC_VER
#	include <windows.h>
#else
#	include <sys/stat.h>
#	include <sys/types.h>
#endif

namespace kl {
	struct file_deleter {
		void operator()(FILE* fd) {
			if (fd != nullptr) {
				std::cout << "close file " << fd << std::endl;

				fclose(fd);
			}
		}
	};

#if defined(_MSC_VER)
	struct handle_deleter {
		void operator()(HANDLE handle) const {
			if (handle != INVALID_HANDLE_VALUE) {
				CloseHandle(handle);
			}
		}
	};

	using handle_unique_ptr = std::unique_ptr<void, handle_deleter>;
#endif
	using file_unique_ptr = std::unique_ptr<FILE, file_deleter>;

	class fs_util {
	public:
		fs_util();
		~fs_util();

		static std::size_t block_size(const std::string& path);
		static std::size_t count_hard_link(const std::string& path);

		static kl::file_unique_ptr make_open_file(const std::string& path, const std::string& mode);
#if defined(_MSC_VER)
		static kl::handle_unique_ptr make_open_handle(HANDLE handle);
#endif
	};
}

#endif /* JNI_FS_FS_UTIL_HPP_ */
