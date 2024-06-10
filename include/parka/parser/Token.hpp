#ifndef PARKA_TOKEN_HPP
#define PARKA_TOKEN_HPP

#include "parka/enum/KeywordType.hpp"
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

		Token(const Snippet& snippet, TokenType type);
		Token(Token&&) = default;
		Token(const Token&) = default;
		Token& operator=(Token&& other) = default;
		Token& operator=(const Token& other) = default;

		static Token initial(const File& file);

		void increment();

		String text() const;
		String category() const;
		const auto& snippet() const { return _snippet; }
		const auto& type() const { return _type; }
		bool isSemicolon() const { return _type == TokenType::Semicolon; }
		bool isIdentifier() const { return _type == TokenType::Identifier; }
		KeywordType getKeywordType() const;

		operator const Snippet&() const { return _snippet; }
		Snippet operator+(const Token& other) const { return _snippet + other._snippet; }
		const auto& operator[](usize index) const { return _snippet[index]; }
		friend std::ostream& operator<<(std::ostream& out, const Token& token);
		
	};

	std::ostream& operator<<(std::ostream& out, TokenType type);
}

#endif
