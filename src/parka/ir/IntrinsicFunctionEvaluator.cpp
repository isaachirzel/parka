#include "parka/evaluation/IntrinsicFunctionEvaluator.hpp"
#include "parka/enum/IntrinsicFunctionType.hpp"
#include "parka/log/Log.hpp"
#include <iostream>

namespace parka::evaluation
{
	static void println(const char *text)
	{
		std::cout << text << std::endl;
	}

	void evaluateIntrinsicFunction(IntrinsicFunctionType intrinsicFunctionType, LocalState&)
	{
		switch (intrinsicFunctionType)
		{
			case IntrinsicFunctionType::Println:
				return println("asdf");
				
			default:
				break;
		}

		log::fatal("Unable to evaluate intrinsic function $.", (int)intrinsicFunctionType);
	}
}
