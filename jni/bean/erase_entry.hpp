#ifndef JNI_BEAN_ERASE_ENTRY_HPP_
#define JNI_BEAN_ERASE_ENTRY_HPP_

#include <tuple>
#include <string>

#include <property/property.hpp>
#include "../state/overwrite_mode.hpp"

namespace kl {

	class erase_entry {
	public:
		erase_entry();
		~erase_entry();

		erase_entry(const erase_entry&) = default;
		erase_entry& operator=(const erase_entry&) = default;

		erase_entry(erase_entry&&) noexcept = default;
		erase_entry& operator=(erase_entry&&) noexcept = default;

		template<std::size_t N>
		decltype(auto) get() const;

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
		overwrite_mode mode;
	};
}

#endif /* JNI_BEAN_ERASE_ENTRY_HPP_ */
