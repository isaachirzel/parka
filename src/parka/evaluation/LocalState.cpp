#include "parka/evaluation/LocalState.hpp"
#include "parka/enum/ReturningType.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/log/Log.hpp"

namespace parka::evaluation
{
	LocalState::LocalState():
		_values(1'048'576),
		_returnValueIndex(0),
		_returningType(ReturningType::None)
	{}

	Value& LocalState::pushValue(const ir::Type& type)
	{
		return _values.push(type);
	}

	Value& LocalState::pushReturnValue(const ir::Type& type)
	{

		auto length = _values.length();
		auto& value = _values.push(type);

		_returnValueIndex = length;

		return value;
	}

	usize LocalState::getReturnValueIndex()
	{
		return _returnValueIndex;
	}

	void LocalState::setReturnValueIndex(usize index)
	{
		_returnValueIndex = index;
	}

	usize LocalState::getScopeIndex()
	{
		return _values.length();
	}

	void LocalState::clearScopeValues(usize index)
	{
		_values.truncate(index);
	}

	void LocalState::setReturning(ReturningType returningType)
	{
		_returningType = returningType;
	}

	Value& LocalState::findValue(const ir::LValueIr& node)
	{
		for (usize i = _values.length(); i-- > 0;)
		{
			auto& value = _values[i];
			
			if (value.nodePtr() == &node)
				return value;
		}

		log::fatal("Unable to get value for node: $", node.symbol());
	}

	Value& LocalState::returnValue()
	{
		assert(_returnValueIndex < _values.length());

		return _values[_returnValueIndex];
	}

	bool LocalState::isReturning() const
	{
		return _returningType != ReturningType::None;
	}
}