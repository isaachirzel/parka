#include "parka/intrinsic/Primitive.hpp"
#include "parka/repository/SyntaxRepository.hpp"
#include "parka/syntax/AdditiveExpressionSyntax.hpp"
#include "parka/syntax/AssignmentExpressionSyntax.hpp"
#include "parka/syntax/BitwiseAndExpressionSyntax.hpp"
#include "parka/syntax/BitwiseOrExpressionSyntax.hpp"
#include "parka/syntax/BitwiseXorExpressionSyntax.hpp"
#include "parka/syntax/BlockSyntax.hpp"
#include "parka/syntax/BooleanAndExpressionSyntax.hpp"
#include "parka/syntax/BooleanOrExpressionSyntax.hpp"
#include "parka/syntax/CallExpressionSyntax.hpp"
#include "parka/syntax/ConditionalExpressionSyntax.hpp"
#include "parka/syntax/EqualityExpressionSyntax.hpp"
#include "parka/syntax/IdentifierExpressionSyntax.hpp"
#include "parka/syntax/IfExpressionSyntax.hpp"
#include "parka/syntax/SubscriptExpressionSyntax.hpp"
#include "parka/syntax/BoolLiteralSyntax.hpp"
#include "parka/syntax/CharLiteralSyntax.hpp"
#include "parka/syntax/FloatLiteralSyntax.hpp"
#include "parka/syntax/IntegerLiteralSyntax.hpp"
#include "parka/syntax/StringLiteralSyntax.hpp"
#include "parka/syntax/MemberAccessExpressionSyntax.hpp"
#include "parka/syntax/MultiplicativeExpressionSyntax.hpp"
#include "parka/syntax/PrefixExpressionSyntax.hpp"
#include "parka/syntax/RelationalExpressionSyntax.hpp"
#include "parka/syntax/ShiftExpressionSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/syntax/ParameterSyntax.hpp"
#include "parka/syntax/VariableSyntax.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/syntax/DeclarationStatementSyntax.hpp"
#include "parka/syntax/ExpressionStatementSyntax.hpp"
#include "parka/syntax/JumpStatementSyntax.hpp"
#include "parka/syntax/StructSyntax.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/repository/ExpressionSyntaxId.hpp"
#include "parka/util/Array.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/util/Pool.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Pool<PackageSyntax> packages(10'000);
	Pool<StructSyntax> structs(100'000);
	Pool<FunctionSyntax> functions(1'000'000);
	Pool<VariableSyntax> variables(10'000'000);
	Pool<ParameterSyntax> parameters(10'000'000);
	Pool<AdditiveExpressionSyntax> additiveExpressions(100'000'000);
	Pool<AssignmentExpressionSyntax> assignmentExpressions(100'000'000);
	Pool<BitwiseAndExpressionSyntax> bitwiseAndExpressions(100'000'000);
	Pool<BitwiseOrExpressionSyntax> bitwiseOrExpressions(100'000'000);
	Pool<BitwiseXorExpressionSyntax> bitwiseXorExpressions(100'000'000);
	Pool<BlockSyntax> blockExpressions(100'000'000);
	Pool<BooleanAndExpressionSyntax> booleanAndExpressions(100'000'000);
	Pool<BooleanOrExpressionSyntax> booleanOrExpressions(100'000'000);
	Pool<CallExpressionSyntax> callExpressions(100'000'000);
	Pool<ConditionalExpressionSyntax> conditionalExpressions(100'000'000);
	Pool<EqualityExpressionSyntax> equalityExpressions(100'000'000);
	Pool<IdentifierExpressionSyntax> identifierExpressions(100'000'000);
	// Pool<IfExpressionSyntax> ifExpressions(100'000'000);
	Pool<SubscriptExpressionSyntax> subscriptExpressions(100'000'000);
	Pool<MemberAccessExpressionSyntax> memberAccessExpressions(100'000'000);
	Pool<MultiplicativeExpressionSyntax> multiplicativeExpressions(100'000'000);
	Pool<PrefixExpressionSyntax> prefixExpressions(100'000'000);
	Pool<RelationalExpressionSyntax> relationalExpressions(100'000'000);
	Pool<ShiftExpressionSyntax> shiftExpressions(100'000'000);
	Pool<DeclarationStatementSyntax> declarationStatements(10'000'000);
	Pool<ExpressionStatementSyntax> expressionStatements(10'000'000);
	Pool<JumpStatementSyntax> jumpStatements(1'000'000);
	Pool<BoolLiteralSyntax> boolLiterals(1'000'000);
	Pool<CharLiteralSyntax> charLiterals(1'000'000);
	Pool<FloatLiteralSyntax> floatLiterals(1'000'000);
	Pool<IntegerLiteralSyntax> integerLiterals(1'000'000);
	Pool<StringLiteralSyntax> stringLiterals(1'000'000);

	EntitySyntaxId SyntaxRepository::add(PackageSyntax&& value)
	{
		usize index = packages.add(std::move(value));

		return EntitySyntaxId(EntityType::PackageSyntax, index);
	}

	EntitySyntaxId SyntaxRepository::add(StructSyntax&& value)
	{
		usize index = structs.add(std::move(value));
		
		return EntitySyntaxId(EntityType::StructSyntax, index);
	}

	EntitySyntaxId SyntaxRepository::add(FunctionSyntax&& value)
	{
		usize index = functions.add(std::move(value));
		
		return EntitySyntaxId(EntityType::Function, index);
	}

	EntitySyntaxId SyntaxRepository::add(VariableSyntax&& value)
	{
		usize index = variables.add(std::move(value));
		
		return EntitySyntaxId(EntityType::Variable, index);
	}

	EntitySyntaxId SyntaxRepository::add(ParameterSyntax&& value)
	{
		usize index = parameters.add(std::move(value));

		return EntitySyntaxId(EntityType::ParameterSyntax, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(AdditiveExpressionSyntax&& value)
	{
		auto index = additiveExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Additive, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(AssignmentExpressionSyntax&& value)
	{
		auto index = assignmentExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Assignment, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(BitwiseAndExpressionSyntax&& value)
	{
		auto index = bitwiseAndExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BitwiseAnd, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(BitwiseOrExpressionSyntax&& value)
	{
		auto index = bitwiseOrExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BitwiseOr, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(BitwiseXorExpressionSyntax&& value)
	{
		auto index = bitwiseXorExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BitwiseXor, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(BlockSyntax&& value)
	{
		auto index = blockExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Block, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(BooleanAndExpressionSyntax&& value)
	{
		auto index = booleanAndExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BooleanAnd, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(BooleanOrExpressionSyntax&& value)
	{
		auto index = booleanOrExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BooleanOr, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(CallExpressionSyntax&& value)
	{
		auto index = callExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Call, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(ConditionalExpressionSyntax&& value)
	{
		auto index = conditionalExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Conditional, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(EqualityExpressionSyntax&& value)
	{
		auto index = equalityExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Equality, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(IdentifierExpressionSyntax&& value)
	{
		auto index = identifierExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::IdentifierExpressionSyntax, index);
	}

	// ExpressionSyntaxId SyntaxRepository::add(IfExpressionSyntax&& value)
	// {
	// 	auto index = ifExpressions.add(std::move(value));

	// 	return ExpressionSyntaxId(ExpressionType::If, index);
	// }

	ExpressionSyntaxId SyntaxRepository::add(SubscriptExpressionSyntax&& value)
	{
		auto index = subscriptExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Subscript, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(MemberAccessExpressionSyntax&& value)
	{
		auto index = memberAccessExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::MemberAccessExpressionSyntax, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(MultiplicativeExpressionSyntax&& value)
	{
		auto index = multiplicativeExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Multiplicative, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(PrefixExpressionSyntax&& value)
	{
		auto index = prefixExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::PrefixExpressionSyntax, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(RelationalExpressionSyntax&& value)
	{
		auto index = relationalExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Relational, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(ShiftExpressionSyntax&& value)
	{
		auto index = shiftExpressions.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::Shift, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(BoolLiteralSyntax&& value)
	{
		auto index = boolLiterals.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::BoolLiteralSyntax, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(CharLiteralSyntax&& value)
	{
		auto index = charLiterals.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::CharLiteralSyntax, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(FloatLiteralSyntax&& value)
	{
		auto index = floatLiterals.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::FloatLiteralSyntax, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(IntegerLiteralSyntax&& value)
	{
		auto index = integerLiterals.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::IntegerLiteralSyntax, index);
	}

	ExpressionSyntaxId SyntaxRepository::add(StringLiteralSyntax&& value)
	{
		auto index = stringLiterals.add(std::move(value));

		return ExpressionSyntaxId(ExpressionType::StringLiteralSyntax, index);
	}

	StatementSyntaxId SyntaxRepository::add(DeclarationStatementSyntax&& value)
	{
		auto index = declarationStatements.add(std::move(value));

		return StatementSyntaxId(StatementType::DeclarationStatementSyntax, index);
	}

	StatementSyntaxId SyntaxRepository::add(ExpressionStatementSyntax&& value)
	{
		auto index = expressionStatements.add(std::move(value));

		return StatementSyntaxId(StatementType::ExpressionSyntax, index);
	}

	StatementSyntaxId SyntaxRepository::add(JumpStatementSyntax&& value)
	{
		auto index = jumpStatements.add(std::move(value));

		return StatementSyntaxId(StatementType::Jump, index);
	}

	EntitySyntax& SyntaxRepository::get(const EntitySyntaxId& id)
	{
		switch (id.type())
		{
			case EntityType::PackageSyntax:
				return packages[id.index()];

			case EntityType::StructSyntax:
				return structs[id.index()];

			case EntityType::Primitive:
				return Primitive::primitives[id.index()];

			case EntityType::Function:
				return functions[id.index()];
				
			case EntityType::Variable:
				return variables[id.index()];

			case EntityType::ParameterSyntax:
				return parameters[id.index()];

			default:
				break;
		}
		
		exitWithError("Unable to get entity of type: $", (int)id.type());
	}

	ExpressionSyntax& SyntaxRepository::get(const ExpressionSyntaxId& id)
	{
		switch (id.type())
		{
			case ExpressionType::Additive:
				return additiveExpressions[id.index()];

			case ExpressionType::Assignment:
				return assignmentExpressions[id.index()];

			case ExpressionType::BitwiseAnd:
				return bitwiseAndExpressions[id.index()];

			case ExpressionType::BitwiseOr:
				return bitwiseOrExpressions[id.index()];

			case ExpressionType::BitwiseXor:
				return bitwiseXorExpressions[id.index()];

			case ExpressionType::Block:
				return blockExpressions[id.index()];

			case ExpressionType::BooleanAnd:
				return booleanAndExpressions[id.index()];

			case ExpressionType::BooleanOr:
				return booleanOrExpressions[id.index()];

			case ExpressionType::Call:
				return callExpressions[id.index()];

			case ExpressionType::Conditional:
				return conditionalExpressions[id.index()];

			case ExpressionType::Equality:
				return equalityExpressions[id.index()];

			case ExpressionType::IdentifierExpressionSyntax:
				return identifierExpressions[id.index()];

			case ExpressionType::If:
				// TODO: Implemente get for If
				break;
				// return ifExpressions[id.index()];

			case ExpressionType::Subscript:
				return subscriptExpressions[id.index()];

			case ExpressionType::MemberAccessExpressionSyntax:
				return memberAccessExpressions[id.index()];

			case ExpressionType::Multiplicative:
				return multiplicativeExpressions[id.index()];

			case ExpressionType::PrefixExpressionSyntax:
				return prefixExpressions[id.index()];

			case ExpressionType::Relational:
				return relationalExpressions[id.index()];

			case ExpressionType::Shift:
				return shiftExpressions[id.index()];

			case ExpressionType::BoolLiteralSyntax:
				return boolLiterals[id.index()];
				
			case ExpressionType::CharLiteralSyntax:
				return charLiterals[id.index()];
				
			case ExpressionType::FloatLiteralSyntax:
				return floatLiterals[id.index()];
				
			case ExpressionType::IntegerLiteralSyntax:
				return integerLiterals[id.index()];
				
			case ExpressionType::StringLiteralSyntax:
				return stringLiterals[id.index()];
				
			default:
				break;
		}

		exitWithError("Unable to get ExpressionSyntax of type: $", (int)id.type());
	}

	StatementSyntax& SyntaxRepository::get(const StatementSyntaxId& id)
	{
		switch (id.type())
		{
			case StatementType::DeclarationStatementSyntax:
				return declarationStatements[id.index()];

			case StatementType::ExpressionSyntax:
				return expressionStatements[id.index()];

			case StatementType::Jump:
				return jumpStatements[id.index()];

			default:
				break;
		}

		exitWithError("Unable to get Statement of type: $", (int)id.type());
	}

	PackageSyntax& SyntaxRepository::getPackage(const EntitySyntaxId& id)
	{
		assert(id.type() == EntityType::PackageSyntax);

		return packages[id.index()];
	}

	StructSyntax& SyntaxRepository::getStruct(const EntitySyntaxId& id)
	{
		assert(id.type() == EntityType::StructSyntax);

		return structs[id.index()];
	}

	FunctionSyntax& SyntaxRepository::getFunction(const EntitySyntaxId& id)
	{
		assert(id.type() == EntityType::Function);

		return functions[id.index()];
	}

	VariableSyntax& SyntaxRepository::getVariable(const EntitySyntaxId& id)
	{
		assert(id.type() == EntityType::Variable);

		return variables[id.index()];
	}

	ParameterSyntax& SyntaxRepository::getParameter(const EntitySyntaxId& id)
	{
		assert(id.type() == EntityType::ParameterSyntax);

		return parameters[id.index()];
	}

	EntitySyntaxId SyntaxRepository::getId(FunctionSyntax& value)
	{
		auto index = functions.getIndex(&value);
		auto id = EntitySyntaxId(EntityType::Function, index);

		return id;
	}

	EntitySyntaxId SyntaxRepository::getId(PackageSyntax& value)
	{
		auto index = packages.getIndex(&value);
		auto id = EntitySyntaxId(EntityType::PackageSyntax, index);

		return id;
	}
}