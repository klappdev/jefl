#ifndef JNI_FS_FS_UTIL_HPP_
#define JNI_FS_FS_UTIL_HPP_

#include <string>

#ifdef _MSC_VER
#	include <windows.h>
#else
#	include <sys/stat.h>
#	include <sys/types.h>
#endif

namespace kl {

	class fs_util {
	public:
		fs_util();
		~fs_util();

		static std::size_t block_size(const std::string& path);
		static std::size_t count_hard_link(const std::string& path);
	};
}

#endif /* JNI_FS_FS_UTIL_HPP_ */
