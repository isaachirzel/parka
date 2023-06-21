#ifndef PARKA_AST_TYPE_ANNOTATION_HPP
#define PARKA_AST_TYPE_ANNOTATION_HPP

#include "parka/ast/QualifiedIdentifier.hpp"
#include "parka/parser/Token.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ir/ValueType.hpp"
#include "parka/util/Optional.hpp"

namespace parka::ast
{
	class TypeAnnotationAst
	{
		Snippet _snippet;
		QualifiedIdentifier _identifier;

	public:

		TypeAnnotationAst(const Snippet& snippet, QualifiedIdentifier&& identifier) :
		_snippet(snippet),
		_identifier(std::move(identifier))
		{}
		TypeAnnotationAst(TypeAnnotationAst&&) = default;
		TypeAnnotationAst(const TypeAnnotationAst&) = delete;

		Optional<ir::ValueType> validate(SymbolTable& symbolTable) const;

		const Snippet& snippet() const { return _snippet; }
		const auto& identifier() const { return _identifier; }
	};
}

#endif
