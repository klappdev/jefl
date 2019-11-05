#ifndef JNI_UTIL_LOG_UTIL_HPP_
#define JNI_UTIL_LOG_UTIL_HPP_

#include <iostream>

#define __DEBUG__ 0

namespace kl {
	class log_util final {
	public:
		log_util() = default;
		~log_util() = default;

		template<typename... Args>
		inline static void debug(Args&&... args) {
#if __DEBUG__ != 0
			(std::cout << ... << args) << '\n';
#endif
		}

		template<typename... Args>
		inline static void error(Args&&... args) {
#if __DEBUG__ != 0
			(std::cerr << ... << args) << '\n';
#endif
		}

		template<typename... Args>
		inline static void log(Args&&... args) {
#if __DEBUG__ != 0
			(std::clog << ... << args) << '\n';
#endif
		}

		template<typename... Args>
		inline static void scan(Args&&... args) {
#if __DEBUG__ != 0
			(std::cin >> ... >> args);
#endif
		}
	};
}

#endif /* JNI_UTIL_LOG_UTIL_HPP_ */
