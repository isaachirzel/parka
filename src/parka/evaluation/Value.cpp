#include "parka/evaluation/Value.hpp"
#include "parka/ir/Type.hpp"
#include "parka/log/Log.hpp"
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
		std::memcpy(_value, other._value, sizeof(_value));

		other._type = ir::Type::voidType;
		other._nodePtr = nullptr;
		std::memset(other._value, 0, sizeof(other._value));
	}

	// Value& Value::operator=(Value&& other)
	// {
	// 	_type = std::move(other._type);
	// 	_nodePtr = other._nodePtr;
	// 	std::memcpy(_value, other._value, sizeof(_value));

	// 	_type = ir::Type::voidType;
	// 	other._nodePtr = nullptr;
	// 	std::memset(other._value, 0, sizeof(other._value));

	// 	return *this;
	// }

	Value& Value::operator=(const Value& other)
	{		
		std::memcpy(_value, other._value, sizeof(_value));

		_type = other._type;
		_nodePtr = other._nodePtr;
		std::memcpy(_value, other._value, sizeof(_value));

		return *this;
	}

	void Value::setNode(const ir::LValue& node)
	{
		_nodePtr = &node;
	}

	void Value::set(const byte* data, usize size)
	{
		assert(size <= sizeof(_value));

		std::memcpy(_value, data, size);
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
