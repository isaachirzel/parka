#include "parka/log/Color.hpp"
#include "parka/util/Array.hpp"

#include <cstring>
#include <ios>

#define BLACK	0
#define RED		1
#define GREEN	2
#define YELLOW	3
#define BLUE	4
#define PURPLE	5
#define CYAN	6
#define WHITE	7
#define COLOR(a, b) ("\033[" #a #b "m")
#define BRIGHT(a) COLOR(9, a)
#define DARK(a) COLOR(3, a)

namespace parka
{
	const Color Color::darkBlack = DARK(BLACK);
	const Color Color::brightBlack = BRIGHT(BLACK);
	const Color Color::darkRed = DARK(RED);
	const Color Color::brightRed = BRIGHT(RED);
	const Color Color::darkGreen = DARK(GREEN);
	const Color Color::brightGreen = BRIGHT(GREEN);
	const Color Color::darkYellow = DARK(YELLOW);
	const Color Color::brightYellow = BRIGHT(YELLOW);
	const Color Color::darkBlue = DARK(BLUE);
	const Color Color::brightBlue = BRIGHT(BLUE);
	const Color Color::darkPurple = DARK(PURPLE);
	const Color Color::brightPurple = BRIGHT(PURPLE);
	const Color Color::darkCyan = DARK(CYAN);
	const Color Color::brightCyan = BRIGHT(CYAN);
	const Color Color::darkWhite = DARK(WHITE);
	const Color Color::brightWhite = BRIGHT(WHITE);
	const Color Color::none = "\033[0m";
	const Color Color::reset = nullptr;
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
			out << Color::none.code();
			
			return out;
		}

		colors->pop();
	
		auto* code = colors->length() > 0
			? colors->back().code()
			: Color::none.code();

		out << code;
		
		return out;
	}
}
