#ifndef PARKA_IR_BOOL_PRIMITIVE_IR_HPP
#define PARKA_IR_BOOL_PRIMITIVE_IR_HPP

#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/TypeNameIr.hpp"

namespace parka::ir
{
	class BoolPrimitiveIr: public TypeIr, public LValueIr
	{
		String _symbol;

	public:

		static BoolPrimitiveIr instance;

	private:

		BoolPrimitiveIr();
		BoolPrimitiveIr(BoolPrimitiveIr&&) = default;
		BoolPrimitiveIr(const BoolPrimitiveIr&) = delete;

	public:

		BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const TypeIr&) const;
		AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const TypeIr&) const;

		std::ostream& printType(std::ostream& out) const;
		const TypeIr& type() const { return TypeNameIr::instance; }
		const String& symbol() const { return _symbol; }
	};
}

#endif
