#ifndef PARKA_AST_TYPE_ANNOTATION_HPP
#define PARKA_AST_TYPE_ANNOTATION_HPP

#include "parka/ast/QualifiedIdentifierAst.hpp"

namespace parka::ast
{
	class TypeAnnotationAst
	{
		Snippet _snippet;
		QualifiedIdentifierAst _identifier;

	public:

		TypeAnnotationAst(const Snippet& snippet, QualifiedIdentifierAst&& identifier):
		_snippet(snippet),
		_identifier(std::move(identifier))
		{}
		TypeAnnotationAst(TypeAnnotationAst&&) = default;
		TypeAnnotationAst(const TypeAnnotationAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const auto& identifier() const { return _identifier; }
	};
}

#endif
