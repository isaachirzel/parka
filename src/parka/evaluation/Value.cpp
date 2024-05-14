#include "parka/evaluation/Value.hpp"
#include "parka/ir/TypeIr.hpp"
#include <cassert>
#include <cstring>

namespace parka::evaluation
{
	Value::Value(const ir::Type& type):
		_type(type),
		_value(),
		_nodePtr(nullptr)
	{
		std::memset(_value, 0, sizeof(_value));
	}

	Value::Value(Value&& other):
		_type(other._type),
		_nodePtr(other._nodePtr)
	{
		memcpy(_value, other._value, sizeof(other._value));

		other._type = ir::Type::voidType;
		other._nodePtr = nullptr;
		memset(other._value, 0, sizeof(other._value));
	}

	void Value::setNode(const ir::LValueIr& node)
	{
		_nodePtr = &node;
	}

	void Value::setValue(const byte* data, usize size)
	{
		assert(size <= sizeof(_value));

		std::memset(_value, 0, sizeof(_value));
		std::memcpy(_value, data, size);
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

		out << "(" << value._type << ") " << *(const i64*)value._value;

		return out;
	}

}
