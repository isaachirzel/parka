#ifndef PARKA_FS_FILE_SNIPPET_HPP
#define PARKA_FS_FILE_SNIPPET_HPP

#include "parka/fs/FilePosition.hpp"
#include "parka/util/Common.hpp"

#include <ostream>

namespace parka::fs
{
	class FileSnippet
	{
		FilePosition _position;
		u32 _length;

	public:

		FileSnippet(const FilePosition& position, u32 length);
		FileSnippet(FileSnippet&&) = default;
		FileSnippet(const FileSnippet&) = default;
		FileSnippet& operator=(const FileSnippet& other);

		const char *ptr() const { return &_position.file()[_position.index()]; }
		const char *begin() const { return &_position.file()[_position.index()]; }
		const char *end() const { return &_position.file()[_position.index() + _length]; }

		const auto& file() const { return _position.file(); }
		const auto& position() const { return _position; }
		const auto& length() const { return _length; }
		
		FilePosition startPosition() const;
		FilePosition endPosition() const;

		FileSnippet operator+(const FileSnippet& other) const;
		FileSnippet& operator+=(const FileSnippet& other);

		bool operator==(const FileSnippet& other) const;
		bool operator!=(const FileSnippet& other) const;


		const auto& operator[](usize index) const { return _position.file()[_position.index() + index]; }
		friend std::ostream& operator<<(std::ostream& out, const FileSnippet& snippet);
	};
}

#endif
