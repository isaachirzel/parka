#include "parka/ast/StringLiteral.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
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
		auto text = _snippet.substr(1, _snippet.length() - 2);
		auto *context = new StringLiteralContext(std::move(text));

		return context;
	}
}
