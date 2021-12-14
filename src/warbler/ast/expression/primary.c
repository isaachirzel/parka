#include <warbler/ast/expression/primary.h>

void expression_free(struct Expression *expression);

void primary_expression_init(PrimaryExpression *primary)
{
	primary->type = PRIMARY_IDENTIFIER;
	primary->identifier = NULL;
}

void primary_expression_free(PrimaryExpression *primary)
{
	assert(primary != NULL);

	switch (primary->type)
	{
		case PRIMARY_IDENTIFIER:
			identifier_free(primary->identifier);
			break;

		case PRIMARY_CONSTANT:
			constant_free(primary->constant);
			break;

		case PRIMARY_EXPRESSION:
			expression_free(primary->expression);			
			break;
	}
}

Error primary_expression_parse(PrimaryExpression *primary, TokenIterator *iter)
{
	assert(primary != NULL);
	assert(iter != NULL);

	return not_implemented_error();
}
