#include <warbler/ast/ast.h>

void ast_init(Ast* ast)
{
	program_init(&ast->program);
}

Error ast_parse(Ast *ast, TokenArray *tokens)
{
	assert(ast);
	assert(tokens);

	ast_init(ast);

	Token *first_token = TokenArray_front_ptr(tokens);
	TokenIterator iter = { first_token };
	Error error = program_parse(&ast->program, &iter);

	return error;
}

void ast_free(Ast *self)
{
	if (!self)
		return;

	program_free(&self->program);
}
