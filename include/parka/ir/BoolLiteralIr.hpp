#ifndef PARKA_IR_BOOL_LITERAL_HPP
#define PARKA_IR_BOOL_LITERAL_HPP

#include "parka/ir/ExpressionIr.hpp"

namespace parka::ir
{
	class BoolLiteralIr: public ExpressionIr
	{
		bool _value;

	public:

		BoolLiteralIr(bool value):
		ExpressionIr(ExpressionType::BoolLiteral),
		_value(value)
		{}
		BoolLiteralIr(BoolLiteralIr&&) = default;
		BoolLiteralIr(const BoolLiteralIr&) = delete;

		const TypeIr& type() const { return TypeIr::boolType; }
		const auto& value() const { return _value; }
	};
}

#endif
