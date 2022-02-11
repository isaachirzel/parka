#ifndef WARBLER_PRINT_HPP
#define WARBLER_PRINT_HPP

// local headers
#include <warbler/token.hpp>
#include <iostream>
#include <string>
#include <sstream>

namespace warbler
{
	void print_enable_color(bool enabled);

	void _debugf(const char *file, unsigned line, const char *func, const char *fmt, ...);
	void _debug(const char *file, unsigned line, const char *func, const char *msg);

	extern std::ostream& error_stream;
	extern std::ostringstream& errout;
	std::string tree_branch(u32 length);
	std::ostream& error_out();
	std::ostream& error_out(const Location& location);
	std::ostream& error_out(const Token& token);
	std::ostream& error_out(TokenIterator& iter);
	
	void error_highlight(const Location& location);
	void error_highlight(const TokenIterator& iter);
	void error_highlight(const Token& token);
	void print_error(const Location& location, const String& msg);
	std::string token_error(TokenIterator& iter);
	std::string token_warning(TokenIterator& iter);
	std::string token_message(TokenIterator& iter);	
	void parse_error(TokenIterator& iter, const char *expected);
}

#ifndef NDEBUG
	#define debugf(fmt, ...) _debugf(__FILE__, __LINE__, __func__, fmt, __VA_ARGS__)
	#define debug(msg) _debug(__FILE__, __LINE__, __func__, msg)
#else
	#define debugf(fmt, ...)
	#define debug(msg)
#endif

#endif
