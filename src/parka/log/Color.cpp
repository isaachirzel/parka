#include "parka/log/Color.hpp"
#include "parka/util/Array.hpp"

#include <cstring>
#include <ios>

namespace parka
{
	const Color Color::Cyan = "\033[96m";
	const Color Color::Blue = "\033[94m";
	const Color Color::Green = "\033[32m";
	const Color Color::Purple = "\033[95m";
	const Color Color::Red = "\033[91m";
	const Color Color::Yellow = "\033[93m";
	const Color Color::Default = "\033[0m";
	const Color Color::Reset = nullptr;
	const int Color::xIndex = std::ios_base::xalloc();
	
	Color::Color(const char *code):
	_code(code)
	{}

	std::ostream& operator<<(std::ostream& out, const Color& color)
	{
		auto *&colorsRef = (Array<Color>*&)out.pword(Color::xIndex);

		if (colorsRef == nullptr)
			colorsRef = new Array<Color>(8);

		auto *colors = colorsRef;

		if (color)
		{
			colors->push(color);
			out << color.code();

			return out;
		}

		if (colors->length() == 0)
		{
			out << Color::Default.code();
			
			return out;
		}

		colors->pop();
	
		auto* code = colors->length() > 0
			? colors->back().code()
			: Color::Default.code();

		out << code;
		
		return out;
	}
}
