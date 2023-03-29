#include "parka/symbol/node_bank.hpp"

#include "parka/ast/expression/additive.hpp"
#include "parka/ast/expression/assignment.hpp"
#include "parka/ast/expression/bitwise_and.hpp"
#include "parka/ast/expression/bitwise_or.hpp"
#include "parka/ast/expression/bitwise_xor.hpp"
#include "parka/ast/expression/block.hpp"
#include "parka/ast/expression/boolean_and.hpp"
#include "parka/ast/expression/boolean_or.hpp"
#include "parka/ast/expression/call.hpp"
#include "parka/ast/expression/conditional.hpp"
#include "parka/ast/expression/equality.hpp"
#include "parka/ast/expression/identifier.hpp"
#include "parka/ast/expression/if.hpp"
#include "parka/ast/expression/index.hpp"
#include "parka/ast/expression/literal/bool.hpp"
#include "parka/ast/expression/literal/char.hpp"
#include "parka/ast/expression/literal/float.hpp"
#include "parka/ast/expression/literal/integer.hpp"
#include "parka/ast/expression/literal/string.hpp"
#include "parka/ast/expression/member_access.hpp"
#include "parka/ast/expression/multiplicative.hpp"
#include "parka/ast/expression/prefix.hpp"
#include "parka/ast/expression/relational.hpp"
#include "parka/ast/expression/shift.hpp"
#include "parka/ast/function/function.hpp"
#include "parka/ast/function/parameter.hpp"
#include "parka/ast/function/variable.hpp"
#include "parka/ast/package.hpp"
#include "parka/ast/statement/declaration.hpp"
#include "parka/ast/statement/expression.hpp"
#include "parka/ast/statement/jump.hpp"
#include "parka/ast/struct.hpp"
#include "parka/symbol/entity_id.hpp"
#include "parka/symbol/expression_id.hpp"
#include "parka/symbol/symbol_table.hpp"
#include "parka/util/array.hpp"
#include "parka/ast/primitive.hpp"
#include "parka/util/pool.hpp"
#include "parka/util/print.hpp"

Array<Primitive> _primitives(14);
Pool<Package> _packages(10'000);
Pool<Struct> _structs(100'000);
Pool<Function> _functions(1'000'000);
Pool<Variable> _variables(10'000'000);
Pool<Parameter> _parameters(10'000'000);
Pool<AdditiveExpression> _additiveExpressions(100'000'000);
Pool<Assignment> _assignmentExpressions(100'000'000);
Pool<BitwiseAndExpression> _bitwiseAndExpressions(100'000'000);
Pool<BitwiseOrExpression> _bitwiseOrExpressions(100'000'000);
Pool<BitwiseXorExpression> _bitwiseXorExpressions(100'000'000);
Pool<Block> _blockExpressions(100'000'000);
Pool<BooleanAndExpression> _booleanAndExpressions(100'000'000);
Pool<BooleanOrExpression> _booleanOrExpressions(100'000'000);
Pool<CallExpression> _callExpressions(100'000'000);
Pool<ConditionalExpression> _conditionalExpressions(100'000'000);
Pool<EqualityExpression> _equalityExpressions(100'000'000);
Pool<Identifier> _identifierExpressions(100'000'000);
Pool<IfExpression> _ifExpressions(100'000'000);
Pool<IndexExpression> _subscriptExpressions(100'000'000);
Pool<MemberAccess> _memberAccessExpressions(100'000'000);
Pool<MultiplicativeExpression> _multiplicativeExpressions(100'000'000);
Pool<Prefix> _prefixExpressions(100'000'000);
Pool<RelationalExpression> _relationalExpressions(100'000'000);
Pool<BitShiftExpression> _shiftExpressions(100'000'000);
Pool<Declaration> _declarationStatements(10'000'000);
Pool<ExpressionStatement> _expressionStatements(10'000'000);
Pool<JumpStatement> _jumpStatements(1'000'000);
Pool<BoolLiteral> _boolLiterals(1'000'000);
Pool<CharLiteral> _charLiterals(1'000'000);
Pool<FloatLiteral> _floatLiterals(1'000'000);
Pool<IntegerLiteral> _integerLiterals(1'000'000);
Pool<StringLiteral> _stringLiterals(1'000'000);

EntityId NodeBank::add(Package&& value)
{
	usize index = _packages.add(std::move(value));

	return EntityId(EntityType::Package, index);
}

EntityId NodeBank::add(Struct&& value)
{
	usize index = _structs.add(std::move(value));
	
	return EntityId(EntityType::Struct, index);
}

EntityId NodeBank::add(Function&& value)
{
	usize index = _functions.add(std::move(value));
	
	return EntityId(EntityType::Function, index);
}

EntityId NodeBank::add(Variable&& value)
{
	usize index = _variables.add(std::move(value));
	
	return EntityId(EntityType::Variable, index);
}

EntityId NodeBank::add(Parameter&& value)
{
	usize index = _parameters.add(std::move(value));

	return EntityId(EntityType::Parameter, index);
}

ExpressionId NodeBank::add(AdditiveExpression&& value)
{
	auto index = _additiveExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::Additive, index);
}

ExpressionId NodeBank::add(Assignment&& value)
{
	auto index = _assignmentExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::Assignment, index);
}

ExpressionId NodeBank::add(BitwiseAndExpression&& value)
{
	auto index = _bitwiseAndExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::BitwiseAnd, index);
}

ExpressionId NodeBank::add(BitwiseOrExpression&& value)
{
	auto index = _bitwiseOrExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::BitwiseOr, index);
}

ExpressionId NodeBank::add(BitwiseXorExpression&& value)
{
	auto index = _bitwiseXorExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::BitwiseXor, index);
}

ExpressionId NodeBank::add(Block&& value)
{
	auto index = _blockExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::Block, index);
}

ExpressionId NodeBank::add(BooleanAndExpression&& value)
{
	auto index = _booleanAndExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::BooleanAnd, index);
}

ExpressionId NodeBank::add(BooleanOrExpression&& value)
{
	auto index = _booleanOrExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::BooleanOr, index);
}

ExpressionId NodeBank::add(CallExpression&& value)
{
	auto index = _callExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::Call, index);
}

ExpressionId NodeBank::add(ConditionalExpression&& value)
{
	auto index = _conditionalExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::Conditional, index);
}

ExpressionId NodeBank::add(EqualityExpression&& value)
{
	auto index = _equalityExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::Equality, index);
}

ExpressionId NodeBank::add(Identifier&& value)
{
	auto index = _identifierExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::Identifier, index);
}

ExpressionId NodeBank::add(IfExpression&& value)
{
	auto index = _ifExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::If, index);
}

ExpressionId NodeBank::add(IndexExpression&& value)
{
	auto index = _subscriptExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::Subscript, index);
}

ExpressionId NodeBank::add(MemberAccess&& value)
{
	auto index = _memberAccessExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::MemberAccess, index);
}

ExpressionId NodeBank::add(MultiplicativeExpression&& value)
{
	auto index = _multiplicativeExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::Multiplicative, index);
}

ExpressionId NodeBank::add(Prefix&& value)
{
	auto index = _prefixExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::Prefix, index);
}

ExpressionId NodeBank::add(RelationalExpression&& value)
{
	auto index = _relationalExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::Relational, index);
}

ExpressionId NodeBank::add(BitShiftExpression&& value)
{
	auto index = _shiftExpressions.add(std::move(value));

	return ExpressionId(ExpressionType::Shift, index);
}

ExpressionId NodeBank::add(BoolLiteral&& value)
{
	auto index = _boolLiterals.add(std::move(value));

	return ExpressionId(ExpressionType::BoolLiteral, index);
}

ExpressionId NodeBank::add(CharLiteral&& value)
{
	auto index = _charLiterals.add(std::move(value));

	return ExpressionId(ExpressionType::CharLiteral, index);
}

ExpressionId NodeBank::add(FloatLiteral&& value)
{
	auto index = _floatLiterals.add(std::move(value));

	return ExpressionId(ExpressionType::FloatLiteral, index);
}

ExpressionId NodeBank::add(IntegerLiteral&& value)
{
	auto index = _integerLiterals.add(std::move(value));

	return ExpressionId(ExpressionType::IntegerLiteral, index);
}

ExpressionId NodeBank::add(StringLiteral&& value)
{
	auto index = _stringLiterals.add(std::move(value));

	return ExpressionId(ExpressionType::StringLiteral, index);
}

StatementId NodeBank::add(Declaration&& value)
{
	auto index = _declarationStatements.add(std::move(value));

	return StatementId(StatementType::Declaration, index);
}

StatementId NodeBank::add(ExpressionStatement&& value)
{
	auto index = _expressionStatements.add(std::move(value));

	return StatementId(StatementType::Expression, index);
}

StatementId NodeBank::add(JumpStatement&& value)
{
	auto index = _jumpStatements.add(std::move(value));

	return StatementId(StatementType::Jump, index);
}

Entity& NodeBank::get(EntityId id)
{
	switch (id.type())
	{
		case EntityType::Package:
			return _packages[id.index()];

		case EntityType::Struct:
			return _structs[id.index()];

		case EntityType::Primitive:
			return _primitives[id.index()];

		case EntityType::Function:
			return _functions[id.index()];
			
		case EntityType::Variable:
			return _variables[id.index()];

		case EntityType::Parameter:
			return _parameters[id.index()];

		default:
			break;
	}
	
	exitWithError("Unable to get entity of type: $", (int)id.type());
}

Expression& NodeBank::get(ExpressionId id)
{
	switch (id.type())
	{
		case ExpressionType::Additive:
			return _additiveExpressions[id.index()];

		case ExpressionType::Assignment:
			return _assignmentExpressions[id.index()];

		case ExpressionType::BitwiseAnd:
			return _bitwiseAndExpressions[id.index()];

		case ExpressionType::BitwiseOr:
			return _bitwiseOrExpressions[id.index()];

		case ExpressionType::BitwiseXor:
			return _bitwiseXorExpressions[id.index()];

		case ExpressionType::Block:
			return _blockExpressions[id.index()];

		case ExpressionType::BooleanAnd:
			return _booleanAndExpressions[id.index()];

		case ExpressionType::BooleanOr:
			return _booleanOrExpressions[id.index()];

		case ExpressionType::Call:
			return _callExpressions[id.index()];

		case ExpressionType::Conditional:
			return _conditionalExpressions[id.index()];

		case ExpressionType::Equality:
			return _equalityExpressions[id.index()];

		case ExpressionType::Identifier:
			return _identifierExpressions[id.index()];

		case ExpressionType::If:
			// TODO: Implemente get for If
			break;
			// return _ifExpressions[id.index()];

		case ExpressionType::Subscript:
			return _subscriptExpressions[id.index()];

		case ExpressionType::MemberAccess:
			return _memberAccessExpressions[id.index()];

		case ExpressionType::Multiplicative:
			return _multiplicativeExpressions[id.index()];

		case ExpressionType::Prefix:
			return _prefixExpressions[id.index()];

		case ExpressionType::Relational:
			return _relationalExpressions[id.index()];

		case ExpressionType::Shift:
			return _shiftExpressions[id.index()];

		case ExpressionType::BoolLiteral:
			return _boolLiterals[id.index()];
			
		case ExpressionType::CharLiteral:
			return _charLiterals[id.index()];
			
		case ExpressionType::FloatLiteral:
			return _floatLiterals[id.index()];
			
		case ExpressionType::IntegerLiteral:
			return _integerLiterals[id.index()];
			
		case ExpressionType::StringLiteral:
			return _stringLiterals[id.index()];
			
		default:
			break;
	}

	exitWithError("Unable to get Expression of type: $", (int)id.type());
}

Statement& NodeBank::get(StatementId id)
{
	switch (id.type())
	{
		case StatementType::Declaration:
			return _declarationStatements[id.index()];

		case StatementType::Expression:
			return _expressionStatements[id.index()];

		case StatementType::Jump:
			return _jumpStatements[id.index()];

		default:
			break;
	}

	exitWithError("Unable to get Statement of type: $", (int)id.type());
}

Package& NodeBank::getPackage(EntityId id)
{
	assert(id.type() == EntityType::Package);

	return _packages[id.index()];
}

Struct& NodeBank::getStruct(EntityId id)
{
	assert(id.type() == EntityType::Struct);

	return _structs[id.index()];
}

Function& NodeBank::getFunction(EntityId id)
{
	assert(id.type() == EntityType::Function);

	return _functions[id.index()];
}

Variable& NodeBank::getVariable(EntityId id)
{
	assert(id.type() == EntityType::Variable);

	return _variables[id.index()];
}

Parameter& NodeBank::getParameter(EntityId id)
{
	assert(id.type() == EntityType::Parameter);

	return _parameters[id.index()];
}

void NodeBank::initialize()
{
	_primitives.push({ "void", PRIMITIVE_VOID, 0 });
	_primitives.push({ "u8", PRIMITIVE_UNSIGNED_INTEGER, 1 });
	_primitives.push({ "u16", PRIMITIVE_UNSIGNED_INTEGER, 2 });
	_primitives.push({ "u32", PRIMITIVE_UNSIGNED_INTEGER, 4 });
	_primitives.push({ "u64", PRIMITIVE_UNSIGNED_INTEGER, 8 });
	_primitives.push({ "i8", PRIMITIVE_SIGNED_INTEGER, 1 });
	_primitives.push({ "i16", PRIMITIVE_SIGNED_INTEGER, 2 });
	_primitives.push({ "i32", PRIMITIVE_SIGNED_INTEGER, 4 });
	_primitives.push({ "i64", PRIMITIVE_SIGNED_INTEGER, 8 });
	_primitives.push({ "f32", PRIMITIVE_FLOATING_POINT, 4 });
	_primitives.push({ "f64", PRIMITIVE_FLOATING_POINT, 8 });
	_primitives.push({ "bool", PRIMITIVE_BOOLEAN, 1 });
	_primitives.push({ "char", PRIMITIVE_CHARACTER, 1 });
	_primitives.push({ "string", PRIMITIVE_STRING, 0 });
}

void NodeBank::declarePrimitives(Table<EntityId>& globalSymbols)
{
	usize index = 0;

	for (const auto& primitive: _primitives)
	{
		globalSymbols.emplace(primitive.symbol(), EntityId { EntityType::Primitive, index });
		
		index += 1;
	}
}

usize NodeBank::getGlobalCount()
{
	return _packages.count() + _structs.count() + _functions.count();
}
