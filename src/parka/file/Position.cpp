#include "parka/file/Position.hpp"
#include <algorithm>

namespace parka
{
	Position::Position(const File& file):
		_file(&file),
		_index(0),
		_line(1),
		_column(1)
	{}

	Position::Position(const File& file, u32 index, u32 line, u32 column):
		_file(&file),
		_index(index),
		_line(line),
		_column(column)
	{}

	void Position::seekEndOfLine()
	{
		const auto& file = *_file;
		auto shouldBreak = false;
		
		while (_index < file.length() && !shouldBreak)
		{
			auto c = file[_index];

			if (c == '\n')
			{
				shouldBreak = true;
				_line += 1;
				_column = 0;
			}

			_index += 1;
			_column += 1;
		}
	}

	void Position::seekEndOfBlockComment()
	{
		const auto& file = *_file;
		auto shouldBreak = false;

		while (_index < file.length() && !shouldBreak)
		{
			auto c = file[_index];

			switch (c)
			{
				case '/':
					if (file[_index - 1] == '*')
						shouldBreak = true;
					break;

				case '\n':
					_line += 1;
					_column = 0;
					break;
			}
			
			_index += 1;
			_column += 1;
		}
	}

	void Position::seekNext()
	{
		const auto& file = *_file;

		while (_index < file.length())
		{
			auto c = file[_index];

			if (c == '/')
			{
				switch (file[_index + 1])
				{
					case '/': // Line comment
						_index += 2;
						seekEndOfLine();
						continue;

					case '*': // Block comment
						_index += 2;
						seekEndOfBlockComment();
						continue;

					default:
						break;
				}
			}

			if (c > ' ')
				break;

			if (c == '\n')
			{
				_line += 1;
				_column = 0;
			}

			_index += 1;
			_column += 1;
		}
	}

	char Position::operator*() const
	{
		return (*_file)[_index];
	}

	char Position::operator[](usize index) const
	{
		return (*_file)[_index + index];
	}

	Position Position::operator+(u32 offset) const
	{
		auto index = std::min(_index + offset, (u32)_file->length());

		return Position(*_file, index, _line, _column + (index - _index));
	}

	bool Position::operator==(const Position& other) const
	{
		return _file == other._file && _index == other._index;
	}

	bool Position::operator!=(const Position& other) const
	{
		return !(*this == other);
	}

	bool Position::operator<(const Position& other) const
	{
		return _index < other._index;
	}

	bool Position::operator<=(const Position& other) const
	{
		return _index <= other._index;
	}

	bool Position::operator>(const Position& other) const
	{
		return _index > other._index;
	}

	bool Position::operator>=(const Position& other) const
	{
		return _index >= other._index;
	}
}
