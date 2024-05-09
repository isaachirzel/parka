#ifndef PARKA_AST_FUNCTION_PROTOTYPE_HPP
#define PARKA_AST_FUNCTION_PROTOTYPE_HPP

#include "parka/ast/IdentifierAst.hpp"
#include "parka/ir/PrototypeIr.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/KeywordAst.hpp"
#include "parka/ast/ParameterAst.hpp"
#include "parka/ast/TypeAnnotationAst.hpp"

namespace parka::ast
{
	class PrototypeAst
	{
		Snippet _snippet;
		Identifier _identifier;
		Array<ParameterAst*> _parameters;
		Result<TypeAnnotationAst> _returnType;

	public:

		PrototypeAst(const Snippet& snippet, Identifier&& identifier, Array<ParameterAst*>&& parameters, Result<TypeAnnotationAst>&& returnType):
		_snippet(snippet),
		_identifier(std::move(identifier)),
		_parameters(std::move(parameters)),
		_returnType(std::move(returnType))
		{}
		PrototypeAst(PrototypeAst&&) = default;
		PrototypeAst(const PrototypeAst&) = delete;

		const auto& snippet() const { return _snippet; }
		const auto& identifier() const { return _identifier; }
		const auto& parameters() const { return _parameters; }
		const auto& returnType() const { return _returnType; }

		friend std::ostream& operator<<(std::ostream& out, const PrototypeAst& syntax);
	};
}

#endif
