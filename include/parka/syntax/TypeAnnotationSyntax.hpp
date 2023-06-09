#ifndef PARKA_SYNTAX_TYPE_ANNOTATION_SYNTAX_HPP
#define PARKA_SYNTAX_TYPE_ANNOTATION_SYNTAX_HPP

#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class TypeAnnotationSyntax
	{
		QualifiedIdentifier _identifier;

	private:

		TypeAnnotationSyntax(QualifiedIdentifier&& identifier);

	public:

		TypeAnnotationSyntax(TypeAnnotationSyntax&&) = default;
		TypeAnnotationSyntax(const TypeAnnotationSyntax&) = delete;

		static Optional<TypeAnnotationSyntax> parse(Token& token);

		const auto& identifier() const { return _identifier; }
	};
}

#endif
