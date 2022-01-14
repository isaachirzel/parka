#ifndef WARBLER_PRINT_HPP
#define WARBLER_PRINT_HPP

// local headers
#include <warbler/token.hpp>
#include <iostream>

namespace warbler
{
	void print_enable_color(bool enabled);
	void print_branch(unsigned count);
	void print_tree_branch_symbol(const char *symbol, unsigned depth);
	void print_spaces(unsigned count);

	void ftprintf(FILE *stream, const char *fmt, ...);
	void tprintf(const char *fmt, ...);
	void errortf(const Token& token, const char *fmt, ...);
	void errort(const Token& token, const char *msg);
	void errorm(const char *msg);
	void errorf(const char *fmt, ...);

	void _debugf(const char *file, unsigned line, const char *func, const char *fmt, ...);
	void _debug(const char *file, unsigned line, const char *func, const char *msg);

	std::ostream& error_out();
	std::ostream& error_out(const Token& token);
	std::ostream& error_out(TokenIterator& iter);
}

#ifndef NDEBUG
	#define debugf(fmt, ...) _debugf(__FILE__, __LINE__, __func__, fmt, __VA_ARGS__)
	#define debug(msg) _debug(__FILE__, __LINE__, __func__, msg)
#else
	#define debugf(fmt, ...)
	#define debug(msg)
#endif

#endif
