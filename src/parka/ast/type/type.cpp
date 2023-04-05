#include "parka/ast/type/type.hpp"
#include "parka/ast/expression/additive.hpp"
#include "parka/ast/expression/literal/literal.hpp"
#include "parka/ast/function/function.hpp"
#include "parka/ast/primitive.hpp"
#include "parka/ast/type/type_annotation.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

const Type Type::voidType(NodeBank::voidId);
const Type Type::u8Type(NodeBank::u8Id);
const Type Type::u16Type(NodeBank::u16Id);
const Type Type::u32Type(NodeBank::u32Id);
const Type Type::u64Type(NodeBank::u64Id);
const Type Type::i8Type(NodeBank::i8Id);
const Type Type::i16Type(NodeBank::i16Id);
const Type Type::i32Type(NodeBank::i32Id);
const Type Type::i64Type(NodeBank::i64Id);
const Type Type::f32Type(NodeBank::f32Id);
const Type Type::f64Type(NodeBank::f64Id);
const Type Type::boolType(NodeBank::boolId);
const Type Type::charType(NodeBank::charId);
const Type Type::stringType(NodeBank::stringId);

String Type::getName() const
{
	auto& entity = NodeBank::get(_entityId);

	return entity.identifier();
}

bool Type::canConvertTo(const Type& to)
{
	return _entityId == to.entityId();
}

std::ostream& operator<<(std::ostream& out, const Type& type)
{
	// output symbol
	auto& entity = NodeBank::get(type.entityId());
	const auto& identifier = entity.identifier();
	out << type.entityId();

	out << identifier;

	return out;
}
