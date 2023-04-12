#ifndef PARKA_CONTEXT_HPP
#define PARKA_CONTEXT_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/repository/ExpressionSyntaxId.hpp"
#include "parka/repository/StatementSyntaxId.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class PackageSyntax;
	class PrimitiveSyntax;
	class StructSyntax;
	class FunctionSyntax;
	class VariableSyntax;
	class ParameterSyntax;
	class AdditiveExpressionSyntax;
	class AssignmentExpressionSyntax;
	class BitwiseAndExpressionSyntax;
	class BitwiseOrExpressionSyntax;
	class BitwiseXorExpressionSyntax;
	class BlockSyntax;
	class BooleanAndExpressionSyntax;
	class BooleanOrExpressionSyntax;
	class CallExpressionSyntax;
	class ConditionalExpressionSyntax;
	class EqualityExpressionSyntax;
	class IdentifierExpressionSyntax;
	class IfExpressionSyntax;
	class SubscriptExpressionSyntax;
	class MemberAccessExpressionSyntax;
	class MultiplicativeExpressionSyntax;
	class PrefixExpressionSyntax;
	class RelationalExpressionSyntax;
	class ShiftExpressionSyntax;
	class BoolLiteralSyntax;
	class CharLiteralSyntax;
	class FloatLiteralSyntax;
	class IntegerLiteralSyntax;
	class StringLiteralSyntax;
	class DeclarationStatementSyntax;
	class ExpressionStatementSyntax;
	class JumpStatementSyntax;

	struct SyntaxRepository
	{
		static EntitySyntaxId add(PackageSyntax&& value);
		static EntitySyntaxId add(StructSyntax&& value);
		static EntitySyntaxId add(FunctionSyntax&& value);
		static EntitySyntaxId add(VariableSyntax&& value);
		static EntitySyntaxId add(ParameterSyntax&& value);

		static ExpressionSyntaxId add(AdditiveExpressionSyntax&& value);
		static ExpressionSyntaxId add(AssignmentExpressionSyntax&& value);
		static ExpressionSyntaxId add(BitwiseAndExpressionSyntax&& value);
		static ExpressionSyntaxId add(BitwiseOrExpressionSyntax&& value);
		static ExpressionSyntaxId add(BitwiseXorExpressionSyntax&& value);
		static ExpressionSyntaxId add(BlockSyntax&& value);
		static ExpressionSyntaxId add(BooleanAndExpressionSyntax&& value);
		static ExpressionSyntaxId add(BooleanOrExpressionSyntax&& value);
		static ExpressionSyntaxId add(CallExpressionSyntax&& value);
		static ExpressionSyntaxId add(ConditionalExpressionSyntax&& value);
		static ExpressionSyntaxId add(EqualityExpressionSyntax&& value);
		static ExpressionSyntaxId add(IdentifierExpressionSyntax&& value);
		static ExpressionSyntaxId add(IfExpressionSyntax&& value);
		static ExpressionSyntaxId add(SubscriptExpressionSyntax&& value);
		static ExpressionSyntaxId add(MemberAccessExpressionSyntax&& value);
		static ExpressionSyntaxId add(MultiplicativeExpressionSyntax&& value);
		static ExpressionSyntaxId add(PrefixExpressionSyntax&& value);
		static ExpressionSyntaxId add(RelationalExpressionSyntax&& value);
		static ExpressionSyntaxId add(ShiftExpressionSyntax&& value);

		static ExpressionSyntaxId add(BoolLiteralSyntax&& value);
		static ExpressionSyntaxId add(CharLiteralSyntax&& value);
		static ExpressionSyntaxId add(FloatLiteralSyntax&& value);
		static ExpressionSyntaxId add(IntegerLiteralSyntax&& value);
		static ExpressionSyntaxId add(StringLiteralSyntax&& value);

		static StatementSyntaxId add(DeclarationStatementSyntax&& value);
		static StatementSyntaxId add(ExpressionStatementSyntax&& value);
		static StatementSyntaxId add(JumpStatementSyntax&& value);

		static EntitySyntax& get(const EntitySyntaxId& id);
		static ExpressionSyntax& get(const ExpressionSyntaxId& id);
		static StatementSyntax& get(const StatementSyntaxId& id);

		static PackageSyntax& getPackage(const EntitySyntaxId& id);
		static StructSyntax& getStruct(const EntitySyntaxId& id);
		static FunctionSyntax& getFunction(const EntitySyntaxId& id);
		static VariableSyntax& getVariable(const EntitySyntaxId& id);
		static ParameterSyntax& getParameter(const EntitySyntaxId& id);

		static EntitySyntaxId getId(FunctionSyntax& value);
		static EntitySyntaxId getId(PackageSyntax& value);
	};
}

#endif
