#include "parka/syntax/BlockSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/repository/Storage.hpp"
#include "parka/Token.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> BlockSyntax::parse(Token& token)
	{
		if (token.type() != TokenType::LeftBrace)
		{
			printParseError(token, "'{' before block");

			return {};
		}

		token.increment();

		// TODO: Add initial capacity
		auto statements = Array<StatementSyntaxId>();

		while (token.type() != TokenType::RightBrace)
		{
			auto statement = StatementSyntax::parse(token);

			if (!statement)
				return {};

			statements.push(*statement);
		}

		token.increment();

		auto block = BlockSyntax(std::move(statements));
		auto id = Storage::add(std::move(block));

		return id;
	}

	// bool Block::validate(const EntitySyntaxId& functionId)
	// {
	// 	auto& function = Storage::getFunction(functionId);
		
	// 	function.pushBlock();

	// 	auto success = true;

	// 	for (auto statement : _statements)
	// 	{
	// 		if (!Storage::get(statement).validate(functionId))
	// 			success = false;
	// 	}

	// 	function.popBlock();

	// 	return success;
	// }
}
