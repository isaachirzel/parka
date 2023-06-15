#ifndef PARKA_SYNTAX_FUNCTION_SYNTAX_HPP
#define PARKA_SYNTAX_FUNCTION_SYNTAX_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Entity.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ast/Prototype.hpp"

namespace parka
{
	class FunctionContext : public EntityContext
	{
		PrototypeContext _prototype;
		ExpressionContext& _body;

	public:

		FunctionContext(PrototypeContext&& prototype, ExpressionContext& body);
		FunctionContext(FunctionContext&&) = default;
		FunctionContext(const FunctionContext&) = delete;

		EntityType entityType() const { return EntityType::Function; }
		const auto& prototype() const { return _prototype; }
		const auto& body() const { return _body; }
	};

	class FunctionSyntax : public EntitySyntax, public SymbolTable
	{
		PrototypeSyntax _prototype;
		ExpressionSyntax& _body;
		// Symbol table data
		SymbolTable *_parent;
		Array<EntitySyntax*> _symbols;

	private:

		bool declareEntity(EntitySyntax& entity);

	public:

		FunctionSyntax(PrototypeSyntax&& prototype, ExpressionSyntax& body);
		FunctionSyntax(FunctionSyntax&&) = default;
		FunctionSyntax(const FunctionSyntax&) = delete;

		static FunctionSyntax *parse(Token& token);
		FunctionContext *validate();
		EntityContext *context() { return validate(); }

		bool declare(EntitySyntax& entity);
		bool declareSelf(SymbolTable& parent);
		EntitySyntax *resolve(const Identifier& identifier);
		EntitySyntax *resolve(const QualifiedIdentifier& identifier);

		SymbolTable *parent() { return _parent; }
		SymbolTableType symbolTableType() const { return SymbolTableType::Function; }
		EntityType entityType() const { return EntityType::Function; }
		const String& name() const { return _prototype.identifier().text(); }
		const auto& identifier() const { return _prototype.identifier(); }
		const auto& prototype() const { return _prototype; }
		const auto& body() const { return _body; }

		friend std::ostream& operator<<(std::ostream& out, const FunctionSyntax& syntax);

		friend class BlockExpressionSyntax;
	};
}

#endif
