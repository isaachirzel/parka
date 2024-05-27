#ifndef PARKA_IR_TYPE_IR_HPP
#define PARKA_IR_TYPE_IR_HPP

#include "parka/enum/AssignmentType.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/enum/TypeCategory.hpp"

namespace parka::ir
{
	class ConversionIr;
	class BinaryOperatorIr;
	class AssignmentOperatorIr;

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
		virtual std::ostream& printType(std::ostream&) const = 0;

		bool operator==(const TypeIr& other) const { return this == &other; }
		bool operator!=(const TypeIr& other) const { return this != &other; }

		friend std::ostream& operator<<(std::ostream& out, const TypeIr& type)
		{
			return type.printType(out);
		}
	};
}

#endif
