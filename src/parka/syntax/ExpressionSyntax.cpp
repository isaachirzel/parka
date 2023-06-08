
#include "parka/log/Log.hpp"
#include "parka/syntax/BitwiseAndExpressionSyntax.hpp"
#include "parka/syntax/BitwiseOrExpressionSyntax.hpp"
#include "parka/syntax/BitwiseXorExpressionSyntax.hpp"
#include "parka/syntax/BoolLiteralSyntax.hpp"
#include "parka/syntax/BooleanAndExpressionSyntax.hpp"
#include "parka/syntax/BooleanOrExpressionSyntax.hpp"
#include "parka/syntax/CallExpressionSyntax.hpp"
#include "parka/syntax/CharLiteralSyntax.hpp"
#include "parka/syntax/ConditionalExpressionSyntax.hpp"
#include "parka/syntax/EqualityExpressionSyntax.hpp"
#include "parka/syntax/ExpressionStatementSyntax.hpp"
#include "parka/syntax/AssignmentExpressionSyntax.hpp"
#include "parka/syntax/AdditiveExpressionSyntax.hpp"
#include "parka/syntax/BlockSyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/FloatLiteralSyntax.hpp"
#include "parka/syntax/IdentifierExpressionSyntax.hpp"
#include "parka/syntax/IntegerLiteralSyntax.hpp"
#include "parka/syntax/MemberAccessExpressionSyntax.hpp"
#include "parka/syntax/MultiplicativeExpressionSyntax.hpp"
#include "parka/syntax/PrefixExpressionSyntax.hpp"
#include "parka/syntax/RelationalExpressionSyntax.hpp"
#include "parka/syntax/ShiftExpressionSyntax.hpp"
#include "parka/syntax/StringLiteralSyntax.hpp"
#include "parka/syntax/SubscriptExpressionSyntax.hpp"
#include "parka/util/Pool.hpp"

namespace parka
{
	static Pool<AdditiveExpressionSyntax> additiveExpressions(100'000'000);
	static Pool<AssignmentExpressionSyntax> assignmentExpressions(100'000'000);
	static Pool<BitwiseAndExpressionSyntax> bitwiseAndExpressions(100'000'000);
	static Pool<BitwiseOrExpressionSyntax> bitwiseOrExpressions(100'000'000);
	static Pool<BitwiseXorExpressionSyntax> bitwiseXorExpressions(100'000'000);
	static Pool<BlockSyntax> blockExpressions(100'000'000);
	static Pool<BooleanAndExpressionSyntax> booleanAndExpressions(100'000'000);
	static Pool<BooleanOrExpressionSyntax> booleanOrExpressions(100'000'000);
	static Pool<CallExpressionSyntax> callExpressions(100'000'000);
	static Pool<ConditionalExpressionSyntax> conditionalExpressions(100'000'000);
	static Pool<EqualityExpressionSyntax> equalityExpressions(100'000'000);
	static Pool<IdentifierExpressionSyntax> identifierExpressions(100'000'000);
	static Pool<SubscriptExpressionSyntax> subscriptExpressions(100'000'000);
	static Pool<MemberAccessExpressionSyntax> memberAccessExpressions(100'000'000);
	static Pool<MultiplicativeExpressionSyntax> multiplicativeExpressions(100'000'000);
	static Pool<PrefixExpressionSyntax> prefixExpressions(100'000'000);
	static Pool<RelationalExpressionSyntax> relationalExpressions(100'000'000);
	static Pool<ShiftExpressionSyntax> shiftExpressions(100'000'000);
	static Pool<BoolLiteralSyntax> boolLiterals(1'000'000);
	static Pool<CharLiteralSyntax> charLiterals(1'000'000);
	static Pool<FloatLiteralSyntax> floatLiterals(1'000'000);
	static Pool<IntegerLiteralSyntax> integerLiterals(1'000'000);
	static Pool<StringLiteralSyntax> stringLiterals(1'000'000);
	
	const ExpressionSyntax *ExpressionSyntax::parse(Token& token)
	{
		if (token.type() == TokenType::LeftBrace)
			return BlockSyntax::parse(token);

		return AssignmentExpressionSyntax::parse(token);
	}

	const ExpressionSyntax& ExpressionSyntax::create(ExpressionSyntax&& syntax)
	{
		const auto type = syntax.expressionType();

		switch (type)
		{
			case ExpressionType::Additive:
				return additiveExpressions.add(std::move((AdditiveExpressionSyntax&)syntax));

			case ExpressionType::Assignment:
				return assignmentExpressions.add(std::move((AssignmentExpressionSyntax&)syntax));

			case ExpressionType::BitwiseAnd:
				return bitwiseAndExpressions.add(std::move((BitwiseAndExpressionSyntax&)syntax));

			case ExpressionType::BitwiseOr:
				return bitwiseOrExpressions.add(std::move((BitwiseOrExpressionSyntax&)syntax));

			case ExpressionType::BitwiseXor:
				return bitwiseXorExpressions.add(std::move((BitwiseXorExpressionSyntax&)syntax));

			case ExpressionType::Block:
				return blockExpressions.add(std::move((BlockSyntax&)syntax));

			case ExpressionType::BooleanAnd:
				return booleanAndExpressions.add(std::move((BooleanAndExpressionSyntax&)syntax));

			case ExpressionType::BooleanOr:
				return booleanOrExpressions.add(std::move((BooleanOrExpressionSyntax&)syntax));

			case ExpressionType::Call:
				return callExpressions.add(std::move((CallExpressionSyntax&)syntax));

			case ExpressionType::Conditional:
				return conditionalExpressions.add(std::move((ConditionalExpressionSyntax&)syntax));

			case ExpressionType::Equality:
				return equalityExpressions.add(std::move((EqualityExpressionSyntax&)syntax));

			case ExpressionType::Identifier:
				return identifierExpressions.add(std::move((IdentifierExpressionSyntax&)syntax));

			case ExpressionType::If:
				// return .add(std::move((&)syntax));
				break;

			case ExpressionType::Subscript:
				return subscriptExpressions.add(std::move((SubscriptExpressionSyntax&)syntax));

			case ExpressionType::MemberAccess:
				return memberAccessExpressions.add(std::move((MemberAccessExpressionSyntax&)syntax));

			case ExpressionType::Multiplicative:
				return multiplicativeExpressions.add(std::move((MultiplicativeExpressionSyntax&)syntax));

			case ExpressionType::Prefix:
				return prefixExpressions.add(std::move((PrefixExpressionSyntax&)syntax));

			case ExpressionType::Relational:
				return relationalExpressions.add(std::move((RelationalExpressionSyntax&)syntax));

			case ExpressionType::Shift:
				return shiftExpressions.add(std::move((ShiftExpressionSyntax&)syntax));

			case ExpressionType::BoolLiteral:
				return boolLiterals.add(std::move((BoolLiteralSyntax&)syntax));

			case ExpressionType::CharLiteral:
				return charLiterals.add(std::move((CharLiteralSyntax&)syntax));

			case ExpressionType::FloatLiteral:
				return floatLiterals.add(std::move((FloatLiteralSyntax&)syntax));

			case ExpressionType::IntegerLiteral:
				return integerLiterals.add(std::move((IntegerLiteralSyntax&)syntax));

			case ExpressionType::StringLiteral:
				return stringLiterals.add(std::move((StringLiteralSyntax&)syntax));


			default:
				break;
		}

		log::fatal("Unable to create ExpressionSyntax with type: $", type);
	}

	ExpressionSyntaxId ExpressionSyntax::idFor(const ExpressionSyntax& syntax)
	{
		const auto type = syntax.expressionType();

		switch (type)
		{
			default:
				break;
		}

		log::fatal("Unable to get Id for ExpressionSyntax with type: &", type);
	}
}
