#ifndef PARKA_VALIDATION_TYPE_CONTEXT_HPP
#define PARKA_VALIDATION_TYPE_CONTEXT_HPP

#include "parka/ir/AssignmentOperatorIr.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/ir/CastIr.hpp"
#include "parka/ir/TypeIr.hpp"

namespace parka::validation
{ 
	struct TypeContext
	{
		~TypeContext() {}

		virtual ir::CastIr* getImplicitCastTo(const ir::TypeIr&) const { return nullptr; }
		virtual ir::CastIr* getExplicitCastTo(const ir::TypeIr&) const { return nullptr; }
		virtual ir::BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const { return nullptr; }
		virtual ir::AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const ir::TypeIr&) const { return nullptr; }
	};
}

#endif
