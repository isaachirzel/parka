#include "parka/syntax/JumpStatementSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/BlockSyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/KeywordSyntax.hpp"

#include "parka/repository/StatementSyntaxId.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<JumpType> getJumpType(Token& token)
	{
		auto keywordType = KeywordSyntax::getKeywordType(token);

		switch (keywordType)
		{
			case KeywordType::Return:
				return JumpType::Return;

			case KeywordType::Break:
				return JumpType::Break;

			case KeywordType::Continue:
				return JumpType::Continue;

			case KeywordType::Yield:
				return JumpType::Yield;

			default:
				Log::parseError(token, "`return`, `break`, `continue` or `yield`");
				return {};
		}
	}

	Optional<StatementSyntaxId> JumpStatementSyntax::parse(Token& token)
	{
		auto type = getJumpType(token);

		if (!type)
			return {};

		// auto name = token;

		token.increment();

		Optional<ExpressionSyntaxId> value;

		if (token.type() != TokenType::Semicolon)
		{
			switch (*type)
			{
				case JumpType::Continue:
					// TODO: Implement continuing on labels
					Log::error(token, "Continue statements cannot have a value.");
					return {};
				
				case JumpType::Break:
					Log::error(token, "Break statements cannot have a value.");
					return {};

				default:
					break;
			}
			
			value = ExpressionSyntax::parse(token);

			if (!value)
				return {};
			
			if (token.type() != TokenType::Semicolon)
			{
				Log::parseError(token, "';' after jump statement", nullptr);
				return {};
			}
		}

		token.increment();

		auto statement = JumpStatementSyntax(token, *type, std::move(value));
		auto id = StatementSyntaxId::create(std::move(statement));

		return id;
	}

	// bool validateReturnStatement(LocalSymbolTable& symbols)
	// {
	// 	if (node->hasValue && !validateExpression(&node->value, symbols))
	// 		return false;

	// 	FunctionSyntax *function = symbols->function;
	// 	const Type *returnType = functionGetReturnType(function);

	// 	Type valueType;
		
	// 	if (node->hasValue)
	// 	{
	// 		if (!expressionGetType(&valueType, &node->value, returnType))
	// 			return false;
	// 	}
	// 	else
	// 	{
	// 		valueType = typeDuplicate(&voidType);
	// 	}
		
	// 	ExpressionSyntax *functionBody = &function->body;

	// 	if (functionBody->type == EXPRESSION_BLOCK)
	// 	{
	// 		Block *block = functionBody->block;

	// 		block->returnType = typeDuplicate(&valueType);
	// 		block->hasReturnType = true;
	// 	}

	// 	if (!typeCanConvert(returnType, &valueType))
	// 	{
	// 		char *returnTypeName = typeGetName(returnType);

	// 		Log::error("Return value is not compatible with return type `$`.", returnTypeName);
	// 		deallocate(returnTypeName);

	// 		return false;
	// 	}

	// 	return true;
	// }

	// bool validateYieldStatement(JumpStatementSyntax *node, LocalSymbolTable& symbols)
	// {
	// 	Block *currentBlock = SymbolTableGetCurrentBlock(symbols);

	// 	if (currentBlock == nullptr)
	// 	{
	// 		Log::error(&node->token, "Yield statement must be within a block.");

	// 		return false;
	// 	}

	// 	const auto& blockReturnType = currentBlock->hasReturnType
	// 		? &currentBlock->returnType
	// 		: &voidType;
	// 	// TODO: Confirm copying type is OK
	// 	Type valueType;
		
	// 	if (node->hasValue)
	// 	{
	// 		if (!expressionGetType(&valueType, &node->value, blockReturnType))
	// 			return false;
	// 	}
	// 	else
	// 	{
	// 		valueType = typeDuplicate(&voidType);
	// 	}

	// 	if (typeCanConvert(blockReturnType, &valueType))
	// 	{
	// 		auto blockTypeName = blockReturnType.getName();
	// 		// TODO: get type token

	// 		Log::error("Yield value is not compatible with type of block expression `$`.", blockTypeName);

	// 		return false;
	// 	}

	// 	return true;
	// }
}
