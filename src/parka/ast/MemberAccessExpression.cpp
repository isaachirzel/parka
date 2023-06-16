#include "parka/ast/MemberAccessExpression.hpp"
#include "parka/log/Log.hpp"

namespace parka::ast
{
	ExpressionAst *MemberAccessExpressionAst::parse(Token& token, ExpressionAst& primary)
	{
		if (token.type() != TokenType::Dot)
		{
			log::parseError(token, "'.'");
			return {};
		}

		token.increment();
		
		if (token.type() != TokenType::Identifier)
		{
			log::parseError(token, "member, method, or property name");
			return {};
		}
		
		auto *syntax = new MemberAccessExpressionAst(primary, Identifier(token));

		token.increment();

		return syntax;
	}

	ir::ExpressionIr *MemberAccessExpressionAst::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}
