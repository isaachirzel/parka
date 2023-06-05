#ifndef PARKA_LOG_COLOR_HPP
#define PARKA_LOG_COLOR_HPP

#include "parka/util/Common.hpp"

#include <ostream>

namespace parka
{
	class Color
	{

		const char *_code;

		Color(const char *code);

	public:

		static const Color Cyan;
		static const Color Blue;
		static const Color Green;
		static const Color Purple;
		static const Color Red;
		static const Color Yellow;
		static const Color Default;
		static const Color Reset;
		static const int xIndex;

	public:

		const auto *code() const { return _code; }
		operator bool() const { return !!_code; }

		friend std::ostream& operator<<(std::ostream& out, const Color& color);
	};
}

#endif
