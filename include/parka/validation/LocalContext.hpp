#ifndef PARKA_VALIDATION_LOCAL_CONTEXT_HPP
#define PARKA_VALIDATION_LOCAL_CONTEXT_HPP

#include "parka/validation/Context.hpp"

namespace parka::validation
{
	class FunctionContext;

	struct LocalContext: public Context
	{
		LocalContext(ContextType symbolTableType):
			Context(symbolTableType)
		{}
		virtual ~LocalContext() {}

		virtual bool isInLoop() const = 0;
		virtual FunctionContext& functionContext() = 0;
		virtual const ir::TypeIr& returnType() const = 0;
	};
}

#endif
