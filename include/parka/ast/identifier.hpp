#ifndef PARKA_AST_IDENTIFIER_HPP
#define PARKA_AST_IDENTIFIER_HPP

#include "parka/token.hpp"
#include "parka/util/optional.hpp"

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
	~Identifier() = default;

	static Optional<Identifier> parse(Token& token);

	const auto& token() const { return _token; }
	const auto& text() const { return _text; }
};

#endif
