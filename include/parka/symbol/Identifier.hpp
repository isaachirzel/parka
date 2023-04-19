#ifndef PARKA_SYNTAX_IDENTIFIER_SYNTAX_HPP
#define PARKA_SYNTAX_IDENTIFIER_SYNTAX_HPP

#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

#include <ostream>

namespace parka
{
	class Identifier
	{
		Token _token;
		String _text;

		Identifier(const Token& token) :
		_token(token),
		_text(token.text())
		{}

	public:

		Identifier(Identifier&&) = default;
		Identifier(const Identifier&) = delete;

		static Optional<Identifier> parse(Token& token);

		friend std::ostream& operator<<(std::ostream& out, const Identifier& identifier);

		const auto& token() const { return _token; }
		const auto& text() const { return _text; }
	};
}

#endif
