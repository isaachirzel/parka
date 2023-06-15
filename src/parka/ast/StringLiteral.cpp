#include "parka/ast/StringLiteral.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	StringLiteralContext::StringLiteralContext(String&& value) :
	_value(std::move(value))
	{}

	StringLiteralSyntax::StringLiteralSyntax(const Token& token) :
	_token(token)
	{}

	ExpressionSyntax *StringLiteralSyntax::parse(Token& token)
	{
		if (token.type() != TokenType::StringLiteralSyntax)
		{
			log::parseError(token, "string");
			return {};
		}

		auto *syntax = new StringLiteralSyntax(token);

		token.increment();

		return syntax;
	}

	ExpressionContext *StringLiteralSyntax::validate(SymbolTable&)
	{
		// TODO: Handle escapes
		const auto& snippet = _token.snippet();
		auto text = snippet.substr(1, snippet.length() - 2);
		auto *context = new StringLiteralContext(std::move(text));

		return context;
	}
}
