#include "parka/ast/CallExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Expression.hpp"

namespace parka::ast
{
	ExpressionAst *CallExpressionAst::parse(Token& token, ExpressionAst& primary)
	{
		auto first = Token(token);
		if (token.type() != TokenType::LeftParenthesis)
		{
			log::parseError(token, "'(' before argument list");
			return {};
		}

		token.increment();

		// TODO: Add initial capacity
		auto arguments = Array<ExpressionAst*>();

		if (token.type() != TokenType::RightParenthesis)
		{
			while (true)
			{
				auto *argument = ExpressionAst::parse(token);

				if (!argument)
					return {}; // TODO: Continue to next argument by checking for ','

				arguments.push(argument);

				if (token.type() != TokenType::Comma)
					break;

				token.increment();
			}

			if (token.type() != TokenType::RightParenthesis)
			{
				log::parseError(token, "')' after argument list");

				return {};
			}
		}

		auto snippet = first + token;

		token.increment();

		auto *syntax = new CallExpressionAst(snippet, primary, std::move(arguments));

		return syntax;
	}

	ir::ExpressionIr *CallExpressionAst::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}
