#ifndef PARKA_EVALUATION_STATE_HPP
#define PARKA_EVALUATION_STATE_HPP

#include "parka/enum/ReturningType.hpp"
#include "parka/evaluation/Value.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/util/BigArray.hpp"
#include "parka/util/Common.hpp"

namespace parka::evaluation
{
	class LocalState
	{
		BigArray<Value> _values;
		usize _returnValueIndex;
		ReturningType _returningType;
		
	public:
		
		LocalState();
		LocalState(LocalState&&) = delete;
		LocalState(const LocalState&) = delete;

		Value& pushValue(const ir::Type& type);
		Value& pushReturnValue(const ir::Type& type);

		usize getReturnValueIndex();
		void setReturnValueIndex(usize index);

		usize getScopeIndex();
		void clearScopeValues(usize index);

		void setReturning(ReturningType returningType);

		Value& findValue(const ir::LValueIr& node);
		Value& returnValue();
		bool isReturning() const;
	};
}

#endif
