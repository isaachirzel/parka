#ifndef PARKA_SYNTAX_TYPE_ANNOTATION_SYNTAX_HPP
#define PARKA_SYNTAX_TYPE_ANNOTATION_SYNTAX_HPP

#include "parka/ast/QualifiedIdentifier.hpp"
#include "parka/Token.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/type/ValueType.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class TypeAnnotationSyntax
	{
		Snippet _snippet;
		QualifiedIdentifier _identifier;

	public:

		TypeAnnotationSyntax(const Snippet& snippet, QualifiedIdentifier&& identifier) :
		_snippet(snippet),
		_identifier(std::move(identifier))
		{}
		TypeAnnotationSyntax(TypeAnnotationSyntax&&) = default;
		TypeAnnotationSyntax(const TypeAnnotationSyntax&) = delete;

		static Optional<TypeAnnotationSyntax> parse(Token& token);

		Optional<ValueType> validate(SymbolTable& symbolTable) const;

		const Snippet& snippet() const { return _snippet; }
		const auto& identifier() const { return _identifier; }
	};
}

#endif
