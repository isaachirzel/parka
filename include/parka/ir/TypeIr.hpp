#ifndef PARKA_IR_TYPE_IR_HPP
#define PARKA_IR_TYPE_IR_HPP

#include "parka/enum/AssignmentType.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/enum/TypeCategory.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	class ConversionIr;
	class BinaryOperatorIr;
	class AssignmentOperatorIr;
	class CallOperatorIr;
	class ExpressionIr;

	struct TypeIr
	{
		const TypeCategory typeCategory;

		TypeIr(TypeCategory typeCategory):
			typeCategory(typeCategory)
		{}
		virtual ~TypeIr() {}

		virtual ConversionIr* getConversion(const TypeIr&) const { return nullptr; }
		virtual BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const TypeIr&) const { return nullptr; }
		virtual AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const TypeIr&) const { return nullptr; }
		virtual CallOperatorIr* getCallOperator(const Array<ExpressionIr*>&) const { return nullptr; }
		virtual std::ostream& printType(std::ostream&) const = 0;

		virtual bool operator==(const TypeIr& other) const { return this == &other; }
		virtual bool operator!=(const TypeIr& other) const { return this != &other; }

		friend std::ostream& operator<<(std::ostream& out, const TypeIr& type)
		{
			return type.printType(out);
		}
	};
}

#endif
