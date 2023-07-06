#ifndef PARKA_EVALUATION_EVALUATOR_HPP
#define PARKA_EVALUATION_EVALUATOR_HPP

#include "parka/ir/Ir.hpp"

namespace parka::evaluation
{
	void evaluate(const ir::Ir& ir);
	void evaluateFunction(const ir::FunctionIr& ir);
	void evaluatePrototype(const ir::PrototypeIr& ir);
	void evaluateExpression(const ir::ExpressionIr& ir);
}

#endif
