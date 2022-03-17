#ifndef WARBLER_UTIL_PRINT_HPP
#define WARBLER_UTIL_PRINT_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/snippet.hpp>
#include <stdexcept>

namespace warbler
{
	std::runtime_error _not_implemented(const char *file, int line, const char *func);
	#define not_implemented() _not_implemented(__FILE__, __LINE__, __func__)

	void print_enable_color(bool enabled);
	
	void print_branch(u32 depth, const String& text);

	void print_note(const Snippet& text, const String& msg);
	void print_warning(const Snippet& text, const String& msg);
	void print_error(const Snippet& text, const String& msg);

	void print_note(const Token& token, const String& msg);
	void print_warning(const Token& token, const String& msg);
	void print_error(const Token& token, const String& msg);

	void print_note(const String& msg);
	void print_warning(const String& msg);
	void print_error(const String& msg);

	void print_parse_error(const Token& token, const String& expected, const String& msg = "");
}

#endif
