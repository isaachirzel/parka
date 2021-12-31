#include <warbler/ast/ast.h>

Error ast_parse(Ast *ast, HxArray *tokens)
{
	assert(ast);
	assert(tokens);
	
	Token *first_token = hxarray_front(tokens);

	TokenIterator iter = 
	{
		.token = first_token
	};
	
	Error error = program_parse(&ast->program, &iter);

	return error;
}

void ast_free(Ast *self)
{
	if (!self)
		return;

	program_free(&self->program);
}
