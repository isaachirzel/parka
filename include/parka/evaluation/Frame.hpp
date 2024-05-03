#ifndef PARKA_EVALUATION_FRAME_HPP
#define PARKA_EVALUATION_FRAME_HPP

#include "parka/util/Common.hpp"

namespace parka::evaluation
{
	class State;

	class Frame
	{

		State& _state;
		usize _start;

		Frame(State& state);

	public:

		~Frame();

		friend class State;
	};
}

#endif
