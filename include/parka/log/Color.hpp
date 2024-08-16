#ifndef PARKA_LOG_COLOR_HPP
#define PARKA_LOG_COLOR_HPP

#include <ostream>

namespace parka::log
{
	class Color
	{
		const char *_code;

	private:

		static const int xIndex;

	public:

		static const Color darkBlack;
		static const Color brightBlack;
		static const Color darkRed;
		static const Color brightRed;
		static const Color darkGreen;
		static const Color brightGreen;
		static const Color darkYellow;
		static const Color brightYellow;
		static const Color darkBlue;
		static const Color brightBlue;
		static const Color darkPurple;
		static const Color brightPurple;
		static const Color darkCyan;
		static const Color brightCyan;
		static const Color darkWhite;
		static const Color brightWhite;
		static const Color none;
		static const Color reset;

	private:

		Color(const char *code);

	public:

		const auto *code() const { return _code; }

		operator bool() const { return !!_code; }

		friend std::ostream& operator<<(std::ostream& out, const Color& color);
	};
}

#endif
