#ifndef PARKA_VALIDATION_TYPE_CONTEXT_HPP
#define PARKA_VALIDATION_TYPE_CONTEXT_HPP

#include "parka/ir/AssignmentOperatorIr.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/ir/CallOperatorIr.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/TypeIr.hpp"

namespace parka::validation
{
	class GlobalContext;

	class TypeContext
	{
		GlobalContext& _globalContext;
		Array<ir::CallOperatorIr> _callOperators;

	public:

		TypeContext(GlobalContext& globalContext):
			_globalContext(globalContext),
			_callOperators()
		{}
		TypeContext(TypeContext&&) = default;
		TypeContext(const TypeContext&) = delete;

		ir::ConversionIr* getConversionTo(const ir::TypeIr&) const;
		ir::BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const ir::TypeIr&) const;
		ir::AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const ir::TypeIr&) const;

		void addCallOperator(ir::CallOperatorIr&& callOperator);
		const ir::CallOperatorIr* getCallOperator(const Array<ir::ExpressionIr*>&) const;
	};
}

#endif
