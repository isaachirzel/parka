#ifndef PARKA_AST_FUNCTION_HPP
#define PARKA_AST_FUNCTION_HPP

#include "parka/entity.hpp"
#include "parka/type.hpp"
#include "parka/ast/expression/expression.hpp"
#include "parka/ast/type_annotation.hpp"
#include "parka/symbol_table.hpp"
#include "parka/util/array.hpp"
#include "parka/util/optional.hpp"

class Function : public Entity
{
	Token _name;
	String _symbol;
	Array<usize> _parameterIds;
	Box<Expression> _body;
	Optional<TypeAnnotation> _returnType;

	Function(const Token& name, String&& symbol, Array<usize>&& parameterIds, Box<Expression>&& body, Optional<TypeAnnotation>&& returnType = {}) :
	_name(name),
	_symbol(std::move(symbol)),
	_parameterIds(std::move(parameterIds)),
	_returnType(std::move(returnType)),
	_body(std::move(body))
	{}

public:

	Function(Function&&) = default;
	Function(const Function&) = delete;
	~Function() = default;

	static Optional<Function> parse(Token& token);

	bool validate(SymbolTable& localTable);
	
	const auto& name() const { return _name; }
	auto token() const { return _name; }
	const auto& symbol() const { return _symbol; }
	auto type() const { return EntityType::Function; }
	const auto& parameterIds() const { return _parameterIds; }
	const auto& body() const { return *_body; }
	const Type& returnType() const;
};

#endif
