#ifndef PARKA_SYNTAX_TYPE_ANNOTATION_SYNTAX_HPP
#define PARKA_SYNTAX_TYPE_ANNOTATION_SYNTAX_HPP

#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/Token.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/type/ValueType.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class TypeAnnotationSyntax
	{
		QualifiedIdentifier _identifier;

	public:

		TypeAnnotationSyntax(QualifiedIdentifier&& identifier);
		TypeAnnotationSyntax(TypeAnnotationSyntax&&) = default;
		TypeAnnotationSyntax(const TypeAnnotationSyntax&) = delete;

		static Optional<TypeAnnotationSyntax> parse(Token& token);

		Optional<ValueType> validate(SymbolTable& symbolTable) const;

		const auto& identifier() const { return _identifier; }
	};
}

#endif
