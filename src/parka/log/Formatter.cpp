// #include "parka/log/FormatStreamBuffer.hpp"
// #include "parka/log/Color.hpp"
// #include <iostream>

// namespace parka
// {
// 	FormatStreamBuffer::FormatStreamBuffer(std::streambuf& destination) :
// 	_destination(destination),
// 	_colors(16),
// 	_indent(0),
// 	_lineNumber(0)
// 	{}

// 	int FormatStreamBuffer::overflow(int ch)
// 	{
// 		auto result = ch == EOF
// 			? sync()
// 			: _destination.sputc(ch);

// 		return result;
// 	}

// 	std::streamsize FormatStreamBuffer::xsputn(const char *src, std::streamsize n)
// 	{
// 		return _destination.sputn(src, n);
// 	}

// 	void FormatStreamBuffer::putColor(const Color& color)
// 	{
// 		_colors.push(&color);
// 		_destination.sputn(color.code(), color.length());
// 	}

// 	void FormatStreamBuffer::popColor()
// 	{
// 		_colors.pop();

// 		const auto& color = _colors.length() > 0
// 			? *_colors.back()
// 			: Color::Default;

// 		_destination.sputn(color.code(), color.length());
// 	}

// 	void FormatStreamBuffer::indent(usize amount)
// 	{
// 		_indent += amount;
// 	}

// 	void FormatStreamBuffer::outdent(usize amount)
// 	{
// 		if (amount >= _indent)
// 		{
// 			_indent = 0;
// 		}
// 		else
// 		{
// 			_indent -= amount;
// 		}
// 	}

// 	void FormatStreamBuffer::line(usize number)
// 	{
// 		_lineNumber = number;
// 	}

// 	void FormatStreamBuffer::reset()
// 	{
// 		_colors.clear();
// 		_destination.sputn(Color::Default.code(), Color::Default.length());
// 		_indent = 0;
// 		_lineNumber = 0;
// 	}
// }
