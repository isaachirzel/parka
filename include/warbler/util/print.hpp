#ifndef WARBLER_UTIL_PRINT_HPP
#define WARBLER_UTIL_PRINT_HPP

// local headers
#include <warbler/lexicon/token.hpp>
#include <warbler/source/snippet.hpp>
#include <stdexcept>

namespace warbler
{
	std::runtime_error _not_implemented(const char *file, int line, const char *func);
	#define not_implemented() _not_implemented(__FILE__, __LINE__, __func__)

	void print_enable_color(bool enabled);
	
	void print_branch(u32 depth, const String& text);

	void print_note(const source::Snippet& text, const String& msg);
	void print_warning(const source::Snippet& text, const String& msg);
	void print_error(const source::Snippet& text, const String& msg);

	void print_note(const lexicon::Token& token, const String& msg);
	void print_warning(const lexicon::Token& token, const String& msg);
	void print_error(const lexicon::Token& token, const String& msg);

	void print_note(const String& msg);
	void print_warning(const String& msg);
	void print_error(const String& msg);

	void print_parse_error(const lexicon::Token& token, const String& expected);
}

#endif
