#ifndef JNI_ERASE_FILE_UNIT_HPP_
#define JNI_ERASE_FILE_UNIT_HPP_

namespace kl::file_literals {
	inline constexpr unsigned long long int operator""_kB(unsigned long long int value) {
		return 1024u * value;
	}

	inline constexpr unsigned long long int operator""_MB(unsigned long long int value) {
		return 1024u * 1024u * value;
	}

	inline constexpr unsigned long long int operator""_GB(unsigned long long int value) {
		return 1024u * 1024u * 1024u * value;
	}
}

#endif /* JNI_ERASE_FILE_UNIT_HPP_ */
