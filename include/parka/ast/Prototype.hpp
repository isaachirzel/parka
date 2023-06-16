#ifndef PARKA_AST_FUNCTION_PROTOTYPE_HPP
#define PARKA_AST_FUNCTION_PROTOTYPE_HPP

#include "parka/ast/Identifier.hpp"
#include "parka/ir/Prototype.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/Parameter.hpp"
#include "parka/ast/TypeAnnotation.hpp"

namespace parka::ast
{
	class PrototypeAst
	{
		Snippet _snippet;
		Identifier _identifier;
		Array<ParameterAst*> _parameters;
		Optional<TypeAnnotationAst> _returnType;

	public:

		PrototypeAst(const Snippet& snippet, Identifier&& identifier, Array<ParameterAst*>&& parameters, Optional<TypeAnnotationAst>&& returnType) :
		_snippet(snippet),
		_identifier(std::move(identifier)),
		_parameters(std::move(parameters)),
		_returnType(std::move(returnType))
		{}
		PrototypeAst(PrototypeAst&&) = default;
		PrototypeAst(const PrototypeAst&) = delete;

		static Optional<PrototypeAst> parse(Token& token);

		Optional<ir::PrototypeIr> validate(SymbolTable& symbolTable);

		const auto& snippet() const { return _snippet; }
		const auto& identifier() const { return _identifier; }
		const auto& parameters() const { return _parameters; }
		const auto& returnType() const { return _returnType; }

		friend std::ostream& operator<<(std::ostream& out, const PrototypeAst& syntax);
	};
}

#endif
