#ifndef PARKA_SYNTAX_FUNCTION_PROTOTYPE_SYNTAX_HPP
#define PARKA_SYNTAX_FUNCTION_PROTOTYPE_SYNTAX_HPP

#include "parka/ast/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/Parameter.hpp"
#include "parka/ast/TypeAnnotation.hpp"

namespace parka
{
	class PrototypeContext
	{
		Array<ParameterContext*> _parameters;
		ValueType _returnType;

	public:

		PrototypeContext(Array<ParameterContext*>&& parameters, ValueType&& returnType) :
		_parameters(std::move(parameters)),
		_returnType(std::move(returnType))
		{}
		PrototypeContext(PrototypeContext&&) = default;
		PrototypeContext(const PrototypeContext&) = delete;

		const auto& parameters() const { return _parameters; }
		const auto& returnType() const { return _returnType; }
	};

	class PrototypeSyntax
	{
		Snippet _snippet;
		Identifier _identifier;
		Array<ParameterSyntax*> _parameters;
		Optional<TypeAnnotationSyntax> _returnType;

	public:

		PrototypeSyntax(const Snippet& snippet, Identifier&& identifier, Array<ParameterSyntax*>&& parameters, Optional<TypeAnnotationSyntax>&& returnType) :
		_snippet(snippet),
		_identifier(std::move(identifier)),
		_parameters(std::move(parameters)),
		_returnType(std::move(returnType))
		{}
		PrototypeSyntax(PrototypeSyntax&&) = default;
		PrototypeSyntax(const PrototypeSyntax&) = delete;

		static Optional<PrototypeSyntax> parse(Token& token);

		Optional<PrototypeContext> validate(SymbolTable& symbolTable);

		const auto& snippet() const { return _snippet; }
		const auto& identifier() const { return _identifier; }
		const auto& parameters() const { return _parameters; }
		const auto& returnType() const { return _returnType; }

		friend std::ostream& operator<<(std::ostream& out, const PrototypeSyntax& syntax);
	};
}

#endif
