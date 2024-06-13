#ifndef PARKA_AST_PARAMETER_HPP
#define PARKA_AST_PARAMETER_HPP

#include "parka/ast/TypeAnnotationAst.hpp"
#include "parka/ast/IdentifierAst.hpp"

namespace parka::ast
{
	class ParameterAst
	{
		Snippet _snippet;
		IdentifierAst _identifier;
		TypeAnnotationAst _annotation;
		bool _isMutable;

	public:

		ParameterAst(const Snippet& snippet, IdentifierAst&& identifier, TypeAnnotationAst&& annotation, bool isMutable);
		ParameterAst(ParameterAst&&) = default;
		ParameterAst(const ParameterAst&) = delete;

		const auto& identifier() const { return _identifier; }		
		const auto& snippet() const { return _snippet; }
		const auto& annotation() const { return _annotation; }
		const auto& isMutable() const { return _isMutable; }

		friend std::ostream& operator<<(std::ostream& out, const ParameterAst& syntax);
	};
}

#endif
