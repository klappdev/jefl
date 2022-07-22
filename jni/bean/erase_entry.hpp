/*
	Copyright (c) 2019 - 2022 https://github.com/klappdev

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
 */

#ifndef JNI_BEAN_ERASE_ENTRY_HPP_
#define JNI_BEAN_ERASE_ENTRY_HPP_

#include <tuple>
#include <string>

#include <property/property.hpp>
#include "../state/overwrite_mode.hpp"

namespace kl {

	class erase_entry {
	public:
		erase_entry() :
			file_name(""),
			file_size(0),
			buffer_size(0),
			mode(kl::overwrite_mode::SIMPLE_MODE) {
		}

		~erase_entry() = default;

		erase_entry(const erase_entry&) = default;
		erase_entry& operator=(const erase_entry&) = default;

		erase_entry(erase_entry&&) noexcept = default;
		erase_entry& operator=(erase_entry&&) noexcept = default;

		template<std::size_t N>
		friend const auto& get(const kl::erase_entry& entry) {
			if constexpr (N == 0) {
				return entry.file_name;
			} else if constexpr (N == 1) {
				return entry.file_size;
			} else if constexpr (N == 2) {
				return entry.buffer_size;
			} else if constexpr (N == 3) {
				return entry.mode;
			}
		}

		SETTER_OBJ_CLR(std::string, file_name);
		SETTER_OBJ_RR(std::string,  file_name);
		GETTER_OBJ_CLR(std::string, file_name);

		SETTER_PRIM(std::uintmax_t, file_size);
		GETTER_PRIM(std::uintmax_t, file_size);

		SETTER_PRIM(std::uint32_t, buffer_size);
		GETTER_PRIM(std::uint32_t, buffer_size);

		SETTER_ENUM(overwrite_mode, mode);
		GETTER_ENUM(overwrite_mode, mode);

	private:
		std::string file_name;
		std::uintmax_t file_size;
		std::uint32_t  buffer_size;
		kl::overwrite_mode mode;
	};
}

namespace std {
	template<>
	struct tuple_size<kl::erase_entry> :
	std::integral_constant<std::size_t, 4> {};

	template<>
	struct tuple_element<0, kl::erase_entry> {
		using type = std::string;
	};

	template<>
	struct tuple_element<1, kl::erase_entry> {
		using type = std::uintmax_t;
	};

	template<>
	struct tuple_element<2, kl::erase_entry> {
		using type = std::uint32_t;
	};

	template<>
	struct tuple_element<3, kl::erase_entry> {
		using type = kl::overwrite_mode;
	};
};

#endif /* JNI_BEAN_ERASE_ENTRY_HPP_ */
