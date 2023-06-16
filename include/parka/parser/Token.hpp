#ifndef PARKA_TOKEN_HPP
#define PARKA_TOKEN_HPP

// local includes
#include "parka/enum/TokenType.hpp"
#include "parka/file/File.hpp"
#include "parka/file/Snippet.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	class Token
	{
		Snippet _snippet;
		TokenType _type;

	public:

		Token(const File& file, usize index, usize length, TokenType type);
		Token(Token&&) = default;
		Token(const Token&) = default;

		static Token initial(const File& file);

		void increment();

		String text() const;
		String category() const;
		// const auto *begin() const { return _snippet.ptr(); }
		// const auto *end() const { return _position.ptr() + _length; }
		// const auto& index() const { return _position.index(); }
		// const auto& file() const { return _snippet.position().file(); }
		// const auto& length() const { return _snippet.length(); }
		const auto& snippet() const { return _snippet; }
		const auto& type() const { return _type; }
		// const auto& position() const { return _snippet.position(); }

		operator const Snippet&() const { return _snippet; }
		// bool operator ==(const Token& other) const;
		// bool operator ==(const String& other) const;
		Snippet operator+(const Token& other) const { return _snippet + other._snippet; }
		const auto& operator[](usize index) const { return _snippet[index]; }
		friend std::ostream& operator<<(std::ostream& out, const Token& token);
	};

	std::ostream& operator<<(std::ostream& out, TokenType type);
}

#endif
