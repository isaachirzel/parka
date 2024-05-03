#include "parka/evaluation/Frame.hpp"
#include "parka/evaluation/State.hpp"

namespace parka::evaluation
{
	Frame::Frame(State& state):
		_state(state),
		_start(state.length())
	{}

	Frame::~Frame()
	{
		_state.truncate(_start);
	}
}
