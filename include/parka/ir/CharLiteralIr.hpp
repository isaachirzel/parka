#ifndef PARKA_IR_CHAR_LITERAL_HPP
#define PARKA_IR_CHAR_LITERAL_HPP

#include "parka/ir/ExpressionIr.hpp"

namespace parka::ir
{
	class CharLiteralIr: public ExpressionIr
	{
		char _value;

	public:

		CharLiteralIr(char value):
		ExpressionIr(ExpressionType::CharLiteral),
		_value(value)
		{}
		CharLiteralIr(CharLiteralIr&&) = default;
		CharLiteralIr(const CharLiteralIr&) = delete;

		const TypeIr& type() const { return TypeIr::charType; }
		const auto& value() const { return _value; }
	};
}

#endif
