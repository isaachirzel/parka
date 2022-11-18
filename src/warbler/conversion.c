// #include <warbler/conversion.h>
// #include <warbler/util/print.h>
// #include <warbler/symbol_table.h>

// static Type getLiteralType(const Literal *literal)
// {
// 	exitNotImplemented();
// }

// static Type getSymbolType(SymbolId *id)
// {
// 	exitNotImplemented();
// }

// static Type getExpressionType(const Expression *expression)
// {
// 	switch (expression->type)
// 	{
// 		case EXPRESSION_BLOCK: // TODO: return type
// 			return (Type) { .id = voidSymbolId };
// 		case EXPRESSION_ASSIGNMENT:
// 			return (Type) { .id = voidSymbolId };
// 		case EXPRESSION_CONDITIONAL:
// 			break;
// 		case EXPRESSION_BOOLEAN_OR:
// 			return (Type) { .id = boolSymbolId };
// 		case EXPRESSION_BOOLEAN_AND:
// 			return (Type) { .id = boolSymbolId };
// 		case EXPRESSION_BITWISE_OR: // TODO: Handle with operator
// 			return getExpressionType(&expression->bitwiseOr->lhs);
// 		case EXPRESSION_BITWISE_XOR: // TODO: Handle with operator
// 			return getExpressionType(&expression->bitwiseXor->lhs);
// 		case EXPRESSION_BITWISE_AND: // TODO: Handle with operator
// 			return getExpressionType(&expression->bitwiseAnd->lhs);
// 		case EXPRESSION_EQUALITY:
// 			return (Type) { .id = boolSymbolId };
// 		case EXPRESSION_RELATIONAL:
// 			return (Type) { .id = boolSymbolId };
// 		case EXPRESSION_SHIFT:
// 			return getExpressionType(&expression->shift->lhs);
// 		case EXPRESSION_ADDITIVE:
// 			return getExpressionType(&expression->additive->lhs);
// 		case EXPRESSION_MULTIPLICATIVE:
// 			return getExpressionType(&expression->additive->lhs);
// 		case EXPRESSION_POSTFIX: // TODO: Figure postfix operation out
// 			break;
// 		case EXPRESSION_PREFIX: // TODO: Figure prefix operation out
// 			break;
// 		case EXPRESSION_LITERAL:
// 			return getLiteralType(expression->literal);
// 		case EXPRESSION_SYMBOL:
// 			return getSymbolType(&expression->symbol.id);
// 	}

// 	exitWithErrorFmt("Invalid expression type: %d", expression->type);
// }

// static bool isLiteralCompatible(const SymbolId *id, LiteralType type)
// {
// 	switch (id->type)
// 	{
// 		case SYMBOL_PACKAGE:
// 			return false;
// 		case SYMBOL_STRUCT:
// 			// return type == LITERAL_OBJECT
// 			return false;
// 		case SYMBOL_PRIMITIVE:
// 		{
// 			exitNotImplemented();
// 		}
// 		case SYMBOL_FUNCTION:
// 			return false;
// 		case SYMBOL_VARIABLE:
// 		{
// 			Variable *variable = symbolTableGetParameter(id);

// 			return isLiteralCompatible(&variable->type.id, type);
// 		}
// 		case SYMBOL_PARAMETER:
// 		{
// 			Parameter *parameter = symbolTableGetParameter(id);

// 			return isLiteralCompatible(&parameter->type.id, type);
// 		}
// 	}

// 	exitWithErrorFmt("Invalid symbol type: %d", id->type);
// }

// void printInvalidConversion(const char *expected, const char *got)
// {
// 	// TODO: Erro hightlights
// 	printError("Expected %s but got %s.", expected, got);
// }

// bool validateImplicitCast(const SymbolId *leftId, const Type *right)
// {
// 	if (right->isLiteral)
// 	{
// 		const Literal *literal = right->literal;

// 		if (isLiteralCompatible(leftId, &literal->type))
// 			return true;

// 		const char *leftTypeName = symbolTableGetSymbol(leftId);
// 		const char *literalTypeName = constantTypeName(literal->type);

// 		printInvalidConversion(leftTypeName, literalTypeName);

// 		return false;
// 	}

// 	const SymbolId *rightId = &right->id;

// 	if (rightId->type == leftId->type && rightId->index == leftId->index)
// 		return true;

// 	const char *leftName = symbolTableGetSymbol(leftId);
// 	const char *rightName = symbolTableGetSymbol(rightId);

// 	printInvalidConversion(leftName, rightName);

// 	return false;
// }

// bool validateExpressionConversion(const Expression *left, const Expression *right)
// {
// 	Type l = getExpressionType(left);
// 	Type r = getExpressionType(right);

// 	return validateConversion(&l, &r);
// }

// /*
// 	conversion
// 		if a & b are compatible:
// 			return true;
		
// 		find conversion between then two

// 		return result of that
// */
