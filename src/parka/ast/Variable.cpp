#include "parka/ast/Variable.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/TypeAnnotation.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	VariableSyntax::VariableSyntax(Identifier&& identifier, bool isMutable, Optional<TypeAnnotationSyntax> annotation) :
	_identifier(std::move(identifier)),
	_annotation(std::move(annotation)),
	_isMutable(isMutable)
	{}

	VariableContext::VariableContext(String&& symbol, ValueType&& type) :
	_symbol(std::move(symbol)),
	_type(std::move(type))
	{}

	VariableSyntax *VariableSyntax::parse(Token& token)
	{
		// TODO: VariableSyntax mutability
		auto keyword = KeywordSyntax::parseVar(token);

		if (!keyword)
			return {};	
		
		auto identifier = Identifier::parse(token);

		if (!identifier)
			return {};

		Optional<TypeAnnotationSyntax> annotation;

		if (token.type() == TokenType::Colon)
		{
			token.increment();

			annotation = TypeAnnotationSyntax::parse(token);

			if (!annotation)
				return {};
		}

		auto *syntax = new VariableSyntax(*identifier, false, std::move(annotation));

		return syntax;
	}

	static Optional<ValueType> validateType(Optional<TypeAnnotationSyntax>& annotation, ExpressionContext *value, SymbolTable& symbolTable)
	{
		if (!annotation)
		{
			if (!value)			
				return {};
			
			return value->valueType();
		}

		auto annotationType = annotation->validate(symbolTable);

		if (!annotationType || !value)
			return {};

		auto valueType = value->valueType();

		if (!valueType.canConvertTo(*annotationType))
		{
			log::error("Unable to initialize variable of type $ with type $.", annotationType, valueType);
			return {};
		}

		return annotationType;
	}

	VariableContext *VariableSyntax::validate(SymbolTable &symbolTable, ExpressionContext *value)
	{
		auto declared = symbolTable.declare(*this);
		auto type = validateType(_annotation, value, symbolTable);

		if (!type || !declared)
			return nullptr;

		auto *context = new VariableContext(String(name()), *type);

		return context;
	}
}
