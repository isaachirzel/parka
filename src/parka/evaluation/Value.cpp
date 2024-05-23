#include "parka/evaluation/Value.hpp"
#include "parka/ir/TypeIr.hpp"
#include <cassert>
#include <cstring>

namespace parka::evaluation
{
	Value::Value(const ir::TypeIr& type):
		_type(type),
		_value(0),
		_nodePtr(nullptr)
	{}

	Value::Value(Value&& other):
		_type(std::move(other._type)),
		_value(other._value),
		_nodePtr(other._nodePtr)
	{
		other._value = 0;
		other._nodePtr = nullptr;
	}

	void Value::setNode(const ir::LValueIr& node)
	{
		_nodePtr = &node;
	}

	void Value::setValue(const byte* data, usize size)
	{
		assert(size <= sizeof(_value));

		_value = 0;

		std::memcpy((byte*)&_value, data, size);
	}

	void Value::setValue(const Value& other)
	{
		assert(_type == other._type);

		setValue(other._value);
	}

	std::ostream& operator<<(std::ostream& out, const Value& value)
	{
		if (value._nodePtr)
		{
			out << value._nodePtr->symbol() << ": " << value._nodePtr->type() << " = ";
		}

		out << "(" << value._type << ") " << (i64)value._value;

		return out;
	}
}
