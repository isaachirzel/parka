#include "parka/log/Color.hpp"
#include "parka/util/Array.hpp"
#include <ios>

namespace parka
{
	namespace color
	{
		bool isEnabled = true;
		Array<Color> stack(8);
	};

	const Color Color::Cyan = "\033[96m";
	const Color Color::Blue = "\033[94m";
	const Color Color::Green = "\033[32m";
	const Color Color::Purple = "\033[95m";
	const Color Color::Red = "\033[91m";
	const Color Color::Yellow = "\033[93m";
	const Color Color::Default = "\033[0m";
	const Color Color::Reset = nullptr;

	void Color::setEnabled(bool enabled)
	{
		color::isEnabled = enabled;
	}

	bool Color::isEnabled()
	{
		return color::isEnabled;
	}

	std::ostream& operator<<(std::ostream& out, const Color& color)
	{
		if (color.code() == nullptr)
		{
			color::stack.pop();

			const auto& previousColor =  color::stack.length() > 0
				? color::stack.back()
				: Color::Default;
			
			out << previousColor.code();
		}
		else
		{
			color::stack.push(Color(color));

			out << color.code();
		}

		return out;
	}
}
