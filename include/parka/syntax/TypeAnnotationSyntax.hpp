#ifndef PARKA_SYNTAX_TYPE_ANNOTATION_SYNTAX_HPP
#define PARKA_SYNTAX_TYPE_ANNOTATION_SYNTAX_HPP

#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/Token.hpp"
#include "parka/type/ValueType.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class TypeAnnotationSyntax
	{
		QualifiedIdentifier _identifier;
		// TODO: Add type after validation
		Optional<ValueType> _type; // Having an optional type is causing this a free warning to come up

		TypeAnnotationSyntax(QualifiedIdentifier&& identifier) :
		_identifier(std::move(identifier)),
		_type()
		{}

	public:

		TypeAnnotationSyntax(TypeAnnotationSyntax&&) = default;
		TypeAnnotationSyntax(const TypeAnnotationSyntax&) = delete;

		static Optional<TypeAnnotationSyntax> parse(Token& token);

		const auto& identifier() const { return _identifier; }
	};
}

#endif
