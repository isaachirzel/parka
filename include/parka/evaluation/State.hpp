#ifndef PARKA_EVALUATION_STATE_HPP
#define PARKA_EVALUATION_STATE_HPP

#include "parka/evaluation/Frame.hpp"
#include "parka/evaluation/Value.hpp"
#include "parka/ir/Type.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Common.hpp"

namespace parka::evaluation
{
	class State
	{
		Array<Value> _stack;
		Value* _returnValue;

	public:
		
		State();

		Value& push(const ir::Type& type, u64 value = 0);
		void pop();
		void truncate(usize length);
		Value& find(const ir::LValue& node);
		Value& get(usize index);
		Frame createFrame();

		usize length() const;
		bool hasReturnValue() const { return !!_returnValue; }
		void returnValue(Value& value) { _returnValue = &value; }
		void clearReturnValue() { _returnValue = nullptr; }
		auto& returnValue() { return *_returnValue; }
	};
}

#endif
