#include "parka/evaluation/State.hpp"
#include "parka/log/Log.hpp"

namespace parka::evaluation
{
	State::State():
		_values()
	{}

	Value& State::push(const ir::Type& type, u64 value)
	{
		return _values.push(Value(type, value));
	}

	void State::pop()
	{
		_values.pop();
	}

	Value& State::get(void *nodePtr)
	{
		for (usize i = _values.length(); i-- > 0;)
		{
			auto& value = _values[i];
			
			if (value.nodePtr() == nodePtr)
				return value;
		}

		log::fatal("Unable to get value for node: $", nodePtr);
	}

	Value& State::get(usize index)
	{
		return _values[index];
	}
	
	void State::truncate(usize length)
	{
		_values.truncate(length);
	}

	Frame State::createFrame()
	{
		auto frame = Frame(*this);

		return frame;
	}

	usize State::length() const
	{
		return _values.length();
	}
}