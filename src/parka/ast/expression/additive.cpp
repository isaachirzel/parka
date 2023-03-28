#include "parka/ast/expression/additive.hpp"
#include "parka/ast/expression/multiplicative.hpp"
#include "parka/ast/primitive.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/symbol/symbol_table.hpp"
#include "parka/util/print.hpp"
#include "parka/util/optional.hpp"

Optional<AdditiveType> getAdditiveType(Token& token)
{
	switch (token.type())
	{
		case TokenType::Plus:
			return ADDITIVE_ADD;

		case TokenType::Minus:
			return ADDITIVE_SUBTRACT;

		default:
			break;
	}

	return {};
}

Optional<ExpressionId> AdditiveExpression::parse(Token& token)
{
	auto lhs = MultiplicativeExpression::parse(token);

	if (!lhs)
		return {};
	
	auto type = getAdditiveType(token);

	while (type)
	{
		token.increment();

		auto rhs = MultiplicativeExpression::parse(token);

		if (!rhs)
			return {};

		auto expression = AdditiveExpression(lhs.unwrap(), rhs.unwrap(), type.unwrap());
		auto id = NodeBank::add(std::move(expression));

		lhs = std::move(id);
		type = getAdditiveType(token);
	}

	return lhs;
}

bool AdditiveExpression::validate(SymbolTable& symbols)
{
	auto success = true;

	if (!NodeBank::get(_lhs).validate(symbols))
		success = false;

	if (!NodeBank::get(_rhs).validate(symbols))
		success = false;

	return {};
}

Optional<Type> getSignedIntegerType(const Primitive& left, const Primitive& right, const Type& expected)
{
	switch (right.primitiveType())
	{
		case PRIMITIVE_SIGNED_INTEGER:
			// TODO: Actually check the bytes
			return Type({ EntityType::Primitive, INDEX_I32 });

		default:
			break;
	}
	
	return {};
}

Optional<Type> getPrimitiveType(const Primitive& left, const Primitive& right, const Type& expected)
{
	exitNotImplemented(here());
	// switch (left.type())
	// {
	// 	case PRIMITIVE_SIGNED_INTEGER:
	// 		return getSignedIntegerType(left, right, expected);

	// 	default:
	// 		break;
	// }

	return {};
}

Optional<Type> AdditiveExpression::getType(const SymbolTable& symbols, Ref<Type> expected) const
{
	exitNotImplemented(here());

	// auto leftType = _lhs->getType(symbols, expected);

	// if (!leftType)
	// 	return {};

	// auto rightType = _rhs->getType(symbols, expected);

	// if (!rightType)
	// 	return {};

	// auto leftId = leftType.value().entityId();

	// if (leftId.type() == EntityType::Primitive)
	// {
	// 	const auto& leftPrimitive = symbols.getEntity(leftId);
	// 	// const Primitive *leftPrimitive = symbolTableGetPrimitive(leftType.value().index());
		
	// 	auto rightId = rightType.value().entityId();

	// 	if (rightId.type() == EntityType::Primitive)
	// 	{
	// 		const Primitive *rightPrimitive = symbolTableGetPrimitive(rightType.value().index());

	// 		auto primitiveType = getPrimitiveType(leftPrimitive, rightPrimitive, expected);

	// 		if (primitiveType)
	// 			return primitiveType;
	// 	}
	// 	else
	// 	{
	// 		exitWithError("Primitive + Complex is not implemented yet.");
	// 	}
	// }
	// else
	// {
	// 	exitWithError("Addition for complex types is not implemented yet.");
	// }
	
	// printError("`%s` cannot be added to `%s`.", rightType.name() typeGetName(&rightType), typeGetName(&leftType));

	return {};
}
