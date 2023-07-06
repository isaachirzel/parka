#include "parka/evaluation/Evaluator.hpp"
#include "parka/log/Log.hpp"

using namespace parka::ir;

namespace parka::evaluation
{
	void evaluate(const Ir& ir)
	{
		auto *entryPoint = ir.entryPoint();

		if (!entryPoint)
		{
			// TODO: Get program name?
			log::error("Unable to evaluate this program as there is no entry point. Please implement a function named `main` in the global scope.");
			return;
		}

		evaluateFunction(*entryPoint);
	}

	void evaluateFunction(const FunctionIr& ir)
	{
		evaluatePrototype(ir.prototype());
		evaluateExpression(ir.body());
	}

	void evaluatePrototype(const PrototypeIr& ir)
	{
	}

	void evaluateExpression(const ExpressionIr& ir)
	{
		switch (ir.expressionType)
		{


			default:
				break;
		}

		log::fatal("Unable to evaluate Expression with Type: $", ir.expressionType);
	}
}
