#ifndef PARKA_FS_FILE_POSITION_HPP
#define PARKA_FS_FILE_POSITION_HPP

#include "parka/fs/File.hpp"
#include "parka/util/Common.hpp"

namespace parka::fs
{
	class FilePosition
	{
		const fs::File* _file;
		u32 _index;
		u16 _line;
		u16 _column;

	public:

		FilePosition(const fs::File& file);
		FilePosition(const fs::File& file, u32 index, u16 line, u16 column);
		FilePosition(FilePosition&&) = default;
		FilePosition(const FilePosition&) = default;
		FilePosition& operator=(FilePosition&&) = default;
		FilePosition& operator=(const FilePosition&) = default;

		void seekBeginningOfLine();
		void seekEndOfLine();
		void seekEndOfBlockComment();
		void seekNext();
		void seek(i32 offset);
		
		char operator*() const;
		char operator[](usize index) const;
		bool operator==(const FilePosition& other) const;
		bool operator!=(const FilePosition& other) const;
		bool operator<(const FilePosition& other) const;
		bool operator<=(const FilePosition& other) const;
		bool operator>(const FilePosition& other) const;
		bool operator>=(const FilePosition& other) const;
		isize operator-(const FilePosition& other) const;

		const auto& file() const { return *_file; }
		const auto& index() const { return _index; }
		const auto& line() const { return _line; }
		const auto& column() const { return _column; }

		friend std::ostream& operator<<(std::ostream& out, const FilePosition& position);
	};
}

#endif
