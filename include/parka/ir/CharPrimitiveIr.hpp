#ifndef PARKA_IR_CHAR_PRIMITIVE_IR_HPP
#define PARKA_IR_CHAR_PRIMITIVE_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/InvalidTypeIr.hpp"

namespace parka::ir
{
	class CharPrimitiveIr: public TypeIr, public LValueIr
	{
		String _symbol;

	public:

		static CharPrimitiveIr instance;

	private:

		CharPrimitiveIr();
		CharPrimitiveIr(CharPrimitiveIr&&) = default;
		CharPrimitiveIr(const CharPrimitiveIr&) = delete;

	public:

		BinaryOperatorIr* getBinaryOperator(BinaryExpressionType, const TypeIr&) const;
		AssignmentOperatorIr* getAssignmentOperator(AssignmentType, const TypeIr&) const;
		std::ostream& printType(std::ostream& out) const;
		
		const TypeIr& type() const { return InvalidTypeIr::typeNameType; }
		const String& symbol() const { return _symbol; }
	};
}

#endif
