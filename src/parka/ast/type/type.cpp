#include "parka/ast/type/type.hpp"
#include "parka/ast/expression/additive.hpp"
#include "parka/ast/expression/literal/literal.hpp"
#include "parka/ast/function/function.hpp"
#include "parka/ast/primitive.hpp"
#include "parka/ast/type/type_annotation.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

const Type Type::voidType = Type(NodeBank::voidId);
const Type Type::i32Type = Type(NodeBank::i32Id);

String Type::getName() const
{
	auto& entity = NodeBank::get(_entityId);

	return entity.identifier();
}

bool Type::canConvertTo(const Type& to)
{
	return _entityId == to.entityId();
}
