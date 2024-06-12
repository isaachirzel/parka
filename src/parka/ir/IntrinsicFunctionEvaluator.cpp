#include "parka/evaluation/IntrinsicFunctionEvaluator.hpp"
#include "parka/enum/IntrinsicFunctionType.hpp"
#include "parka/log/Log.hpp"
#include <utility>

namespace parka::evaluation
{
	static void printInt(i64 value)
	{
		std::cout << value << std::endl;
	}

	static void println(const char* text)
	{
		std::cout << text << std::endl;
	}

	template <typename T>
	T param(LocalState& state, usize index)
	{
		auto& parameter = state.getParameter(index);
		auto& value = parameter.getValue<T>();

		return value;
	}

	template<typename ...Args, typename Int, Int ...Ints>
	void _call(void (*func)(Args...), LocalState& state, std::integer_sequence<Int, Ints...>)
	{
		func(param<Args>(state, Ints)...);
	}

	template<typename ...Args>
	void call(void (*func)(Args...), LocalState& state)
	{
		return _call(func, state, std::index_sequence_for<Args...>());
	}

	void evaluateIntrinsicFunction(IntrinsicFunctionType intrinsicFunctionType, LocalState& state)
	{
		switch (intrinsicFunctionType)
		{
			case IntrinsicFunctionType::Println:
				return call(println, state);

			case IntrinsicFunctionType::PrintInt:
				return call(printInt, state);

			default:
				break;
		}

		log::fatal("Unable to evaluate intrinsic function $.", (int)intrinsicFunctionType);
	}
}
