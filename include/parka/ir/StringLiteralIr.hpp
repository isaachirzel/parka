#ifndef PARKA_IR_STRING_LITERAL_HPP
#define PARKA_IR_STRING_LITERAL_HPP

#include "parka/ir/ExpressionIr.hpp"

namespace parka::ir
{
	class StringLiteralIr: public ExpressionIr
	{
		String _value;

	public:

		StringLiteralIr(String&& value):
		ExpressionIr(ExpressionType::StringLiteral),
		_value(std::move(value))
		{}
		StringLiteralIr(StringLiteralIr&&) = default;
		StringLiteralIr(const StringLiteralIr&) = delete;

		const Type& type() const { return Type::stringType; }
		const auto& value() const { return _value; }
	};
}

#endif
