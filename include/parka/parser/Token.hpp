#ifndef PARKA_TOKEN_HPP
#define PARKA_TOKEN_HPP

#include "parka/enum/KeywordType.hpp"
#include "parka/enum/TokenType.hpp"
#include "parka/fs/File.hpp"
#include "parka/fs/FileSnippet.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	class Token
	{
		fs::FileSnippet _snippet;
		TokenType _type;

	public:

		Token(const fs::FileSnippet& snippet, TokenType type);
		Token(Token&&) = default;
		Token(const Token&) = default;
		Token& operator=(Token&& other) = default;
		Token& operator=(const Token& other) = default;

		static Token initial(const fs::File& file);

		void increment();

		String category() const;
		const auto& snippet() const { return _snippet; }
		const auto& type() const { return _type; }
		bool isSemicolon() const { return _type == TokenType::Semicolon; }
		bool isIdentifier() const { return _type == TokenType::Identifier; }
		KeywordType getKeywordType() const;

		operator const fs::FileSnippet&() const { return _snippet; }
		fs::FileSnippet operator+(const Token& other) const { return _snippet + other._snippet; }
		const auto& operator[](usize index) const { return _snippet[index]; }
		friend std::ostream& operator<<(std::ostream& out, const Token& token);
		
	};

	std::ostream& operator<<(std::ostream& out, TokenType type);
}

#endif
