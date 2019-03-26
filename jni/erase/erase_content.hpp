#ifndef JNI_ERASE_ERASE_CONTENT_HPP_
#define JNI_ERASE_ERASE_CONTENT_HPP_

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace kl {

	class erase_content {
	public:
		erase_content();
		~erase_content();

		void show_permision(fs::perms permision);
	};
}

#endif /* JNI_ERASE_ERASE_CONTENT_HPP_ */
