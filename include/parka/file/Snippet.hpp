#ifndef PARKA_FILE_SNIPPET_HPP
#define PARKA_FILE_SNIPPET_HPP

#include "parka/file/File.hpp"
#include "parka/file/Position.hpp"
#include "parka/util/Common.hpp"

#include <ostream>

// TODO: Optimize the text call?

namespace parka
{
	class Snippet
	{
		Position _position;
		u32 _length;

	public:

		Snippet(const Position& position, u32 length);
		Snippet(Snippet&&) = default;
		Snippet(const Snippet&) = default;

		const char *ptr() const { return &_position.file()[_position.index()]; }
		const char *begin() const { return &_position.file()[_position.index()]; }
		const char *end() const { return &_position.file()[_position.index() + _length]; }

		const auto& file() const { return _position.file(); }
		const auto& position() const { return _position; }
		const auto& length() const { return _length; }
		
		Snippet sub(usize offset, usize length) const;

		Snippet& operator=(const Snippet& other);
		Snippet operator+(const Snippet& other) const;
		bool operator==(const Snippet& other) const;
		bool operator!=(const Snippet& other) const;
		const auto& operator[](usize index) const { return _position.file()[_position.index() + index]; }
		friend std::ostream& operator<<(std::ostream& out, const Snippet& snippet);
	};
}

#endif
