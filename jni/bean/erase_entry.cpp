#include "erase_entry.hpp"

kl::erase_entry::erase_entry() :
	fd(0),
	file_name(""),   file_size(0),
	buffer(nullptr), buffer_size(0),
	mode(kl::overwrite_mode::SIMPLE_MODE) {}

kl::erase_entry::~erase_entry() {}
