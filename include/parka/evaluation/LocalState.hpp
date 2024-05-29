#ifndef PARKA_EVALUATION_STATE_HPP
#define PARKA_EVALUATION_STATE_HPP

#include "parka/enum/JumpType.hpp"
#include "parka/evaluation/GlobalState.hpp"
#include "parka/evaluation/Value.hpp"
#include "parka/ir/EntityIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/util/BigArray.hpp"
#include "parka/util/Common.hpp"

namespace parka::evaluation
{
	class LocalState
	{
		GlobalState& _globalState;
		BigArray<Value> _values;
		usize _returnValueIndex;
		JumpType _jumpType;
		
	public:
		
		LocalState(GlobalState& globalState);
		LocalState(LocalState&&) = delete;
		LocalState(const LocalState&) = delete;

		Value& pushValue(const ir::TypeIr& type);
		Value& pushReturnValue(const ir::TypeIr& type);

		usize getReturnValueIndex();
		void setReturnValueIndex(usize index);

		usize getScopeIndex();
		void clearScopeValues(usize index);

		void setReturning(JumpType returningType);

		Value& findValue(const ir::EntityIr& node);
		Value& returnValue();
		void startBreak() { _jumpType = JumpType::Break; }
		void cancelBreak() { if (_jumpType == JumpType::Break) _jumpType = JumpType::None; }
		void cancelContinue() { if (_jumpType == JumpType::Continue) _jumpType = JumpType::None; }
		void startContinue() { _jumpType = JumpType::Continue; }
		bool isJumping() const { return _jumpType != JumpType::None; }
		bool isBreaking() const { return _jumpType == JumpType::Break; }
		bool isContinuing() const { return _jumpType == JumpType::Continue; }
		bool isReturning() const { return _jumpType == JumpType::Return; }
	};
}

#endif
