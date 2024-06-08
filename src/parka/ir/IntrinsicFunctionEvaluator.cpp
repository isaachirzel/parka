#include "parka/evaluation/IntrinsicFunctionEvaluator.hpp"
#include "parka/enum/IntrinsicFunctionType.hpp"
#include "parka/log/Log.hpp"
#include <iostream>

namespace parka::evaluation
{
	void evaluateIntrinsicFunction(IntrinsicFunctionType intrinsicFunctionType, LocalState&)
	{
		switch (intrinsicFunctionType)
		{
			case IntrinsicFunctionType::Print:
				std::cout << "PRINT" << std::endl;
				return;
				
			default:
				break;
		}

		log::fatal("Unable to evaluate intrinsic function $.", (int)intrinsicFunctionType);
	}
}
