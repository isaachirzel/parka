#ifndef PARKA_EVALUATION_INTEGER_VALUE_HPP
#define PARKA_EVALUATION_INTEGER_VALUE_HPP

#include "parka/evaluation/Value.hpp"
#include "parka/ir/IntegerLiteral.hpp"
#include "parka/util/Common.hpp"

namespace parka::evaluation
{
	class IntegerValue: public Value
	{
		
		ir::Type _type;
		i64 _value;

	public:

		IntegerValue(const ir::Type& type, i64 value):
		_type(type),
		_value(value)
		{}
		IntegerValue(IntegerValue&&) = default;
		IntegerValue(const IntegerValue&) = delete;

		Value& add(const Value& other) const;

		const ir::Type& type() const { return _type; }
		const auto& value() const { return _value; }
	};
}

#endif
