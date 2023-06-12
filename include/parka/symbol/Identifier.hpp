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

	public:

		Identifier(const Token& token);
		Identifier(Identifier&&) = default;
		Identifier(const Identifier&) = delete;

		static Optional<Identifier> parse(Token& token);

		const auto& token() const { return _token; }
		const auto& text() const { return _text; }

		friend std::ostream& operator<<(std::ostream& out, const Identifier& identifier);
	};
}

#endif
