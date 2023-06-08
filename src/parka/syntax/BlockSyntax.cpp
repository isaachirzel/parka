#include "parka/syntax/BlockSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/Token.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	const ExpressionSyntax *BlockSyntax::parse(Token& token)
	{
		if (token.type() != TokenType::LeftBrace)
		{
			log::parseError(token, "'{' before block");

			return {};
		}

		token.increment();

		// TODO: Add initial capacity
		auto statements = Array<const StatementSyntax*>();

		while (token.type() != TokenType::RightBrace)
		{
			auto statement = StatementSyntax::parse(token);

			if (!statement)
				return {};

			statements.push(statement);
		}

		token.increment();

		auto block = BlockSyntax(std::move(statements));
		auto& syntax = ExpressionSyntax::create(std::move(block));

		return &syntax;
	}

	// bool Block::validate(const EntitySyntax& function)
	// {
	// 	auto& function = SyntaxRepository::getFunction(function);
		
	// 	function.pushBlock();

	// 	auto success = true;

	// 	for (auto statement : _statements)
	// 	{
	// 		if (!SyntaxRepository::get(statement).validate(function))
	// 			success = false;
	// 	}

	// 	function.popBlock();

	// 	return success;
	// }
}
