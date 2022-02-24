#ifndef WARBLER_UTIL_PRINT_HPP
#define WARBLER_UTIL_PRINT_HPP

// local headers
#include <warbler/lexicon/token.hpp>
#include <warbler/source/text.hpp>

namespace warbler
{
	void print_enable_color(bool enabled);

	String tree_branch(u32 length);
	void print_branch(u32 depth, const String& text);

	void print_note(const source::Snippet& text, const String& msg);
	void print_warning(const source::Snippet& text, const String& msg);
	void print_error(const source::Snippet& text, const String& msg);

	inline void print_note(const source::Location& location, const String& msg) { print_note(location.get_snippet(), msg); }
	inline void print_warning(const source::Location& location, const String& msg) { print_warning(location.get_snippet(), msg); }
	inline void print_error(const source::Location& location, const String& msg) { print_error(location.get_snippet(), msg); }

	void print_note(const String& msg);
	void print_warning(const String& msg);
	void print_error(const String& msg);

	void print_parse_error(lexicon::TokenIterator& iter, const String& expected);
}

#endif
