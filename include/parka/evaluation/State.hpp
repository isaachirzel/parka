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
		Array<Value> _values;

	public:
		
		State();

		Value& push(const ir::Type& type, u64 value = 0);
		void pop();
		void truncate(usize length);
		Value& get(void *nodePtr);
		Value& get(usize index);
		Frame createFrame();

		usize length() const;
	};
}

#endif
