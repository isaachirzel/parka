#ifndef PARKA_FILE_POSITION_HPP
#define PARKA_FILE_POSITION_HPP

#include "parka/file/File.hpp"
#include "parka/util/Common.hpp"

namespace parka
{
	class Position
	{
		const File* _file;
		u32 _index;
		u32 _line;
		u32 _column;

	public:

		Position(const File& file);
		Position(const File& file, u32 index, u32 line, u32 column);
		Position(Position&&) = default;
		Position(const Position&) = default;
		Position& operator=(Position&&) = default;
		Position& operator=(const Position&) = default;

		void seekEndOfLine();
		void seekEndOfBlockComment();
		void seekNext();

		char operator*() const;
		char operator[](usize index) const;
		Position operator+(u32 offset) const;
		bool operator==(const Position& other) const;
		bool operator!=(const Position& other) const;
		bool operator<(const Position& other) const;
		bool operator<=(const Position& other) const;
		bool operator>(const Position& other) const;
		bool operator>=(const Position& other) const;

		const auto& file() const { return *_file; }
		const auto& index() const { return _index; }
		const auto& line() const { return _line; }
		const auto& column() const { return _column; }
	};
}

#endif
