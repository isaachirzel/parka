#ifndef PARKA_CONTEXT_FUNCTION_CONTEXT_HPP
#define PARKA_CONTEXT_FUNCTION_CONTEXT_HPP

#include "parka/context/ExpressionContext.hpp"
#include "parka/context/PrototypeContext.hpp"
#include "parka/enum/EntityType.hpp"
#include "parka/repository/EntityContext.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class FunctionContext : public EntityContext
	{
		PrototypeContext _prototype;
		ExpressionContext& _body;

	public:

		FunctionContext(PrototypeContext&& prototype, ExpressionContext& body) :
		_prototype(std::move(prototype)),
		_body(body)
		{}
		FunctionContext(FunctionContext&&) = default;
		FunctionContext(const FunctionContext&) = delete;

		EntityType entityType() const { return EntityType::Function; }
		const auto& prototype() const { return _prototype; }
		const auto& body() const { return _body; }
	};
}

#endif
