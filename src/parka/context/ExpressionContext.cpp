#include "parka/context/ExpressionContext.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Pool.hpp"

namespace parka
{
	// static Pool<AdditiveExpressionContext> additiveExpressions(100'000'000);
	// static Pool<AssignmentExpressionContext> assignmentExpressions(100'000'000);
	// static Pool<BitwiseAndExpressionContext> bitwiseAndExpressions(100'000'000);
	// static Pool<BitwiseOrExpressionContext> bitwiseOrExpressions(100'000'000);
	// static Pool<BitwiseXorExpressionContext> bitwiseXorExpressions(100'000'000);
	// static Pool<BlockContext> blockExpressions(100'000'000);
	// static Pool<BooleanAndExpressionContext> booleanAndExpressions(100'000'000);
	// static Pool<BooleanOrExpressionContext> booleanOrExpressions(100'000'000);
	// static Pool<CallExpressionContext> callExpressions(100'000'000);
	// static Pool<ConditionalExpressionContext> conditionalExpressions(100'000'000);
	// static Pool<EqualityExpressionContext> equalityExpressions(100'000'000);
	// static Pool<IdentifierExpressionContext> identifierExpressions(100'000'000);
	// static Pool<SubscriptExpressionContext> subscriptExpressions(100'000'000);
	// static Pool<MemberAccessExpressionContext> memberAccessExpressions(100'000'000);
	// static Pool<MultiplicativeExpressionContext> multiplicativeExpressions(100'000'000);
	// static Pool<PrefixExpressionContext> prefixExpressions(100'000'000);
	// static Pool<RelationalExpressionContext> relationalExpressions(100'000'000);
	// static Pool<ShiftExpressionContext> shiftExpressions(100'000'000);
	// static Pool<BoolLiteralContext> boolLiterals(1'000'000);
	// static Pool<CharLiteralContext> charLiterals(1'000'000);
	// static Pool<FloatLiteralContext> floatLiterals(1'000'000);
	// static Pool<IntegerLiteralContext> integerLiterals(1'000'000);
	// static Pool<StringLiteralContext> stringLiterals(1'000'000);

	const ExpressionContext *ExpressionContext::validate(const ExpressionSyntax& syntax, SymbolTable& symbolTable)
	{
		log::error("ExpressionContext::validate is not implemented");
		return nullptr;
	}

	const ExpressionContext& ExpressionContext::create(ExpressionContext&& context)
	{
		const auto type = context.expressionType();

		switch (type)
		{
			// case ExpressionType::Additive:
			// 	return additiveExpressions.add(std::move((AdditiveExpressionContext&)Context));

			// case ExpressionType::Assignment:
			// 	return assignmentExpressions.add(std::move((AssignmentExpressionContext&)Context));

			// case ExpressionType::BitwiseAnd:
			// 	return bitwiseAndExpressions.add(std::move((BitwiseAndExpressionContext&)Context));

			// case ExpressionType::BitwiseOr:
			// 	return bitwiseOrExpressions.add(std::move((BitwiseOrExpressionContext&)Context));

			// case ExpressionType::BitwiseXor:
			// 	return bitwiseXorExpressions.add(std::move((BitwiseXorExpressionContext&)Context));

			// case ExpressionType::Block:
			// 	return blockExpressions.add(std::move((BlockContext&)Context));

			// case ExpressionType::BooleanAnd:
			// 	return booleanAndExpressions.add(std::move((BooleanAndExpressionContext&)Context));

			// case ExpressionType::BooleanOr:
			// 	return booleanOrExpressions.add(std::move((BooleanOrExpressionContext&)Context));

			// case ExpressionType::Call:
			// 	return callExpressions.add(std::move((CallExpressionContext&)Context));

			// case ExpressionType::Conditional:
			// 	return conditionalExpressions.add(std::move((ConditionalExpressionContext&)Context));

			// case ExpressionType::Equality:
			// 	return equalityExpressions.add(std::move((EqualityExpressionContext&)Context));

			// case ExpressionType::Identifier:
			// 	return identifierExpressions.add(std::move((IdentifierExpressionContext&)Context));

			// case ExpressionType::If:
			// 	// return .add(std::move((&)Context));
			// 	break;

			// case ExpressionType::Subscript:
			// 	return subscriptExpressions.add(std::move((SubscriptExpressionContext&)Context));

			// case ExpressionType::MemberAccess:
			// 	return memberAccessExpressions.add(std::move((MemberAccessExpressionContext&)Context));

			// case ExpressionType::Multiplicative:
			// 	return multiplicativeExpressions.add(std::move((MultiplicativeExpressionContext&)Context));

			// case ExpressionType::Prefix:
			// 	return prefixExpressions.add(std::move((PrefixExpressionContext&)Context));

			// case ExpressionType::Relational:
			// 	return relationalExpressions.add(std::move((RelationalExpressionContext&)Context));

			// case ExpressionType::Shift:
			// 	return shiftExpressions.add(std::move((ShiftExpressionContext&)Context));

			// case ExpressionType::BoolLiteral:
			// 	return boolLiterals.add(std::move((BoolLiteralContext&)Context));

			// case ExpressionType::CharLiteral:
			// 	return charLiterals.add(std::move((CharLiteralContext&)Context));

			// case ExpressionType::FloatLiteral:
			// 	return floatLiterals.add(std::move((FloatLiteralContext&)Context));

			// case ExpressionType::IntegerLiteral:
			// 	return integerLiterals.add(std::move((IntegerLiteralContext&)Context));

			// case ExpressionType::StringLiteral:
			// 	return stringLiterals.add(std::move((StringLiteralContext&)Context));

			default:
				break;
		}

		log::fatal("Unable to create ExpressionContext with type: $", type);
	}

	ExpressionContextId ExpressionContext::idFor(const ExpressionContext& Context)
	{
		const auto type = Context.expressionType();

		switch (type)
		{
			default:
				break;
		}

		log::fatal("Unable to get Id for ExpressionContext with type: &", type);
	}
}