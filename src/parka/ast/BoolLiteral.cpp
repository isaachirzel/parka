#include "parka/ast/BoolLiteral.hpp"
#include "parka/ir/BoolLiteral.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Keyword.hpp"

namespace parka::ast
{
	static Optional<bool> parseBool(Token& token)
	{
		auto type = KeywordAst::getKeywordType(token);

		switch (type)
		{
			case KeywordType::True:
				return true;

			case KeywordType::False:
				return false;

			default:
				break;
		}

		log::parseError(token, "`true` or `false`");
		
		return {};
	}

	ExpressionAst *BoolLiteralAst::parse(Token& token)
	{
		auto value = parseBool(token);

		if (!value)
			return {};

		auto *syntax = new BoolLiteralAst(token, *value);

		token.increment();

		return syntax;
	}

	ir::ExpressionIr *BoolLiteralAst::validate(SymbolTable&)
	{
		return new ir::BoolLiteralIr(_value);
	}
}
