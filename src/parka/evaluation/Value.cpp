#include "parka/evaluation/Value.hpp"
#include "parka/log/Log.hpp"
#include <cassert>

namespace parka::evaluation
{
	Value::Value(const ir::Type& type, u64 value):
		_type(type),
		_value(value),
		_nodePtr(nullptr)
	{}

	void Value::nodePtr(void *nodePtr)
	{
		_nodePtr = nodePtr;
	}

	void* Value::nodePtr()
	{
		return _nodePtr;
	}

	void Value::set(const Value& other)
	{
		// TODO: handle actual conversion

		if (_type != other._type)
			log::fatal("Unable to convert $ to $.", other.type(), _type);

		_value = other._value;
	}	

	std::ostream& operator<<(std::ostream& out, const Value& value)
	{
		out << value._type << ": " << value._value;

		return out;
	}

}
