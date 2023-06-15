#ifndef PARKA_TOKEN_HPP
#define PARKA_TOKEN_HPP

// local includes
#include "parka/enum/TokenType.hpp"
#include "parka/file/File.hpp"
#include "parka/file/FilePosition.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	class Token
	{
		FilePosition _position;
		usize _length;
		TokenType _type;

	public:

		Token(const File& file, usize index, usize length, TokenType type) :
		_position(file, index),
		_length(length),
		_type(type)
		{}
		Token(Token&&) = default;
		Token(const Token&) = default;

		static Token initial(const File& file);

		void increment();

		bool operator ==(const Token& other) const;
		bool operator ==(const String& other) const;
		const auto& operator[](usize index) const { return _position.file()[index]; }

		String substr(usize pos, usize length) const;
		String text() const;
		String category() const;
		const auto *begin() const { return _position.ptr(); }
		const auto *end() const { return _position.ptr() + _length; }
		const auto& file() const { return _position.file(); }
		const auto& index() const { return _position.index(); }
		const auto& length() const { return _length; }
		const auto& type() const { return _type; }
		const auto& position() const { return _position; }

		friend std::ostream& operator<<(std::ostream& out, const Token& token);
	};

	std::ostream& operator<<(std::ostream& out, TokenType type);
}

#endif
