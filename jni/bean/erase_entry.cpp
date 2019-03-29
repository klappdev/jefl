#include "erase_entry.hpp"

kl::erase_entry::erase_entry() :
	file_name(""),  file_size(0),
	buffer_size(0), mode(kl::overwrite_mode::SIMPLE_MODE) {}

kl::erase_entry::~erase_entry() {}

template<std::size_t N>
decltype(auto) kl::erase_entry::get() const {
	if constexpr (N == 0) {
		return (file_name);
	} else if constexpr (N == 1) {
		return file_size;
	} else if constexpr (N == 2) {
		return buffer_size;
	} else if constexpr (N == 3) {
		return mode;
	}
}

template<>
struct std::tuple_size<kl::erase_entry> :
std::integral_constant<std::size_t, 4> {};

template<std::size_t N>
struct std::tuple_element<N, kl::erase_entry> {
	using type = decltype(std::declval<kl::erase_entry>().get<N>());
};
