#include "parka/type.hpp"
#include "parka/ast/expression/additive.hpp"
#include "parka/ast/expression/literal.hpp"
#include "parka/ast/function.hpp"
#include "parka/ast/primitive.hpp"
#include "parka/symbol.hpp"
#include "parka/global_symbol_table.hpp"
#include "parka/util/print.hpp"

const Type voidType = { INDEX_VOID, EntityType::Primitive };
const Type i32Type = { INDEX_I32, EntityType::Primitive };

void typeFree(Type *type)
{
	assert(type);
	// TODO: pointers
}

Optional<TypeAnnotation> TypeAnnotation::parse(Token& token)
{
	if (token.type() != TokenType::Identifier)
	{
		printParseError(token, "type", NULL);
		return false;
	}
	
	out->token = *token;

	token.increment();

	return true;
}

bool validateTypeAnnotation(TypeAnnotation *node, const Scope *packageScope)
{
	assert(node != NULL);
	assert(packageScope != NULL);

	const Token& token = &node->token;
	EntityContext *symbol = symbolTableResolveGlobal(packageScope, token);

	if (!symbol)
		return false;

	switch (symbol->type)
	{
		case EntityType::Struct:
		case EntityType::Primitive:
			node->type = (Type)
			{
				.type = symbol->type,
				.index = symbol->index
			};

			return true;

		default:
			break;
	}

	const char *typeName = entityTypeGetName(symbol->type);

	printTokenError(token, "Expected type name, found %s.", typeName);

	return false;
}

void typeAnnotationFree(TypeAnnotation *node)
{
	typeFree(&node->type);
}

String Type::getName() const
{
	EntityContext *symbol = symbolTableGetSymbol(type->index);
	char *name = stringDuplicate(symbol->key);

	return name;
}

bool Type::canConvertTo(const Type& to)
{
	auto canConvert = _type == to.type()
		&& _index == to.index();

	return canConvert;
}
