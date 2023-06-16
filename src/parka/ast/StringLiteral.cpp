#include "parka/ast/StringLiteral.hpp"
#include "parka/ir/StringLiteral.hpp"
#include "parka/log/Log.hpp"

namespace parka::ast
{
	ExpressionAst *StringLiteralAst::parse(Token& token)
	{
		if (token.type() != TokenType::StringLiteralAst)
		{
			log::parseError(token, "string");
			return {};
		}

		auto *syntax = new StringLiteralAst(token);

		token.increment();

		return syntax;
	}

	ir::ExpressionIr *StringLiteralAst::validate(SymbolTable&)
	{
		// TODO: Handle escapes
		auto text = _snippet.substr(1, _snippet.length() - 2);
		auto *context = new ir::StringLiteralIr(std::move(text));

		return context;
	}
}
