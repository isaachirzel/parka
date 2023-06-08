#ifndef PARKA_CONTEXT_FUNCTION_CONTEXT_HPP
#define PARKA_CONTEXT_FUNCTION_CONTEXT_HPP

#include "parka/context/PrototypeContext.hpp"
#include "parka/enum/EntityType.hpp"
#include "parka/repository/EntityContext.hpp"
#include "parka/repository/EntityContextId.hpp"
#include "parka/repository/ExpressionContextId.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class FunctionContext : public EntityContext
	{
		PrototypeContext _prototype;
		ExpressionContextId _bodyId;

		FunctionContext()
		{}

	public:

		FunctionContext(FunctionContext&&) = default;
		FunctionContext(const FunctionContext&) = delete;

		static const FunctionContext *validate(FunctionSymbolTable& symbolTable);

		EntityType type() const { return EntityType::Function; }
	};
}

#endif
