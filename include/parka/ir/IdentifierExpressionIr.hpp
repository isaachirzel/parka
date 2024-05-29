#ifndef PARKA_IR_IDENTIFIER_EXPRESSION_HPP
#define PARKA_IR_IDENTIFIER_EXPRESSION_HPP

#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/EntityIr.hpp"

namespace parka::ir
{
	class IdentifierExpressionIr: public ExpressionIr
	{
		EntityIr& _entity;

	public:

		IdentifierExpressionIr(EntityIr& entity):
			ExpressionIr(ExpressionType::Identifier),
			_entity(entity)
		{}
		IdentifierExpressionIr(IdentifierExpressionIr&&) = default;
		IdentifierExpressionIr(const IdentifierExpressionIr&) = delete;

		const auto& entity() const { return _entity; }
		const TypeIr& type() const { return _entity.type(); }
	};
}

#endif
