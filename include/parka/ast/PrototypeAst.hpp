#ifndef PARKA_AST_FUNCTION_PROTOTYPE_HPP
#define PARKA_AST_FUNCTION_PROTOTYPE_HPP

#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/ParameterAst.hpp"
#include "parka/ast/TypeAnnotationAst.hpp"
#include "parka/util/Result.hpp"

namespace parka::ast
{
	class PrototypeAst
	{
		fs::FileSnippet _snippet;
		IdentifierAst _identifier;
		Array<ParameterAst*> _parameters;
		Result<TypeAnnotationAst> _returnType;

	public:

		PrototypeAst(const fs::FileSnippet& snippet, IdentifierAst&& identifier, Array<ParameterAst*>&& parameters, Result<TypeAnnotationAst>&& returnType):
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
	};
}

#endif
