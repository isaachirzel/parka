#ifndef PARKA_AST_FUNCTION_HPP
#define PARKA_AST_FUNCTION_HPP

#include "parka/ast/function/prototype.hpp"
#include "parka/symbol/entity.hpp"
#include "parka/symbol/symbol_table.hpp"
#include "parka/symbol/symbol_table.hpp"
#include "parka/type.hpp"
#include "parka/ast/expression/expression.hpp"
#include "parka/ast/type_annotation.hpp"

#include "parka/util/array.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/string.hpp"

class Function : public Entity
{
	String _symbol;
	Prototype _prototype;
	ExpressionId _body;

	Function(String&& symbol, Prototype&& prototype, ExpressionId&& body) :
	_symbol(std::move(symbol)),
	_prototype(std::move(prototype)),
	_body(std::move(body))
	{}

public:

	Function(Function&&) = default;
	Function(const Function&) = delete;
	~Function() = default;

	static Optional<EntityId> parse(Token& token, const String& package);

	bool validate(SymbolTable& symbols);
	
	Token token() const { return _prototype.name(); }
	const String& symbol() const { return _symbol; }
	EntityType type() const { return EntityType::Function; }
	const auto& body() const { return _body; }
	Type getReturnType() const;
};

#endif
