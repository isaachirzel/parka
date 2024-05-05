#include "parka/evaluation/State.hpp"
#include "parka/ir/LValue.hpp"
#include "parka/log/Log.hpp"

namespace parka::evaluation
{
	State::State():
		_stack(),
		_returnValue(nullptr)
	{}

	Value& State::push(const ir::Type& type, u64 value)
	{
		return _stack.push(Value(type, value));
	}

	void State::pop()
	{
		_stack.pop();
	}

	Value& State::find(const ir::LValue& node)
	{
		for (usize i = _stack.length(); i-- > 0;)
		{
			auto& value = _stack[i];
			
			if (value.nodePtr() == &node)
				return value;
		}

		log::fatal("Unable to get value for node: $", node.symbol());
	}

	Value& State::get(usize index)
	{
		return _stack[index];
	}
	
	void State::truncate(usize length)
	{
		_stack.truncate(length);
	}

	Frame State::createFrame()
	{
		auto frame = Frame(*this);

		return frame;
	}

	usize State::length() const
	{
		return _stack.length();
	}
}