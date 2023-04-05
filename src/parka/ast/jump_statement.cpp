#include "parka/ast/jump_statement.hpp"
#include "parka/ast/block.hpp"
#include "parka/ast/expression.hpp"
#include "parka/ast/keyword.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/node/statement_id.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/print.hpp"

Optional<JumpType> getJumpType(Token& token)
{
	auto keywordType = Keyword::getKeywordType(token);

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
			printParseError(token, "`return`, `break`, `continue` or `yield`");
			return {};
	}
}

Optional<StatementId> JumpStatement::parse(Token& token)
{
	auto type = getJumpType(token);

	if (!type)
		return {};

	auto name = token;

	token.increment();

	Optional<ExpressionId> value;

	if (token.type() != TokenType::Semicolon)
	{
		switch (*type)
		{
			case JumpType::Continue:
				// TODO: Implement continuing on labels
				printError(token, "Continue statements cannot have a value.");
				return {};
			
			case JumpType::Break:
				printError(token, "Break statements cannot have a value.");
				return {};

			default:
				break;
		}
		
		value = Expression::parse(token);

		if (!value)
			return {};
		
		if (token.type() != TokenType::Semicolon)
		{
			printParseError(token, "';' after jump statement", NULL);
			return {};
		}
	}

	token.increment();

	auto statement = JumpStatement(token, *type, std::move(value));
	auto id = NodeBank::add(std::move(statement));

	return id;
}

// bool validateReturnStatement(LocalSymbolTable& symbols)
// {
// 	if (node->hasValue && !validateExpression(&node->value, symbols))
// 		return false;

// 	Function *function = symbols->function;
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
	
// 	Expression *functionBody = &function->body;

// 	if (functionBody->type == EXPRESSION_BLOCK)
// 	{
// 		Block *block = functionBody->block;

// 		block->returnType = typeDuplicate(&valueType);
// 		block->hasReturnType = true;
// 	}

// 	if (!typeCanConvert(returnType, &valueType))
// 	{
// 		char *returnTypeName = typeGetName(returnType);

// 		printError("Return value is not compatible with return type `$`.", returnTypeName);
// 		deallocate(returnTypeName);

// 		return false;
// 	}

// 	return true;
// }

// bool validateYieldStatement(JumpStatement *node, LocalSymbolTable& symbols)
// {
// 	Block *currentBlock = SymbolTableGetCurrentBlock(symbols);

// 	if (currentBlock == NULL)
// 	{
// 		printError(&node->token, "Yield statement must be within a block.");

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

// 		printError("Yield value is not compatible with type of block expression `$`.", blockTypeName);

// 		return false;
// 	}

// 	return true;
// }

bool JumpStatement::validate(const EntityId&)
{
	exitNotImplemented(here());
	// switch (node->type)
	// {
	// 	case JUMP_RETURN:
	// 		return validateReturnStatement(node, symbols);

	// 	case JUMP_BREAK:
	// 		break;

	// 	case JUMP_CONTINUE:
	// 		break;

	// 	case JUMP_YIELD:
	// 		return validateYieldStatement(node, symbols);

	// 	default:
	// 		break;
	// }
	
	// exitWithError("Unable to validate JumpStatement with type: $", node->type);
}
