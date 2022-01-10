#include <warbler/ast/ast.hpp>

namespace warbler
{
	void ast_init(Ast* ast)
	{
		program_init(&ast->program);
	}

	Error ast_parse(Ast *ast, const std::vector<Token>& tokens)
	{
		assert(ast != NULL);

		ast_init(ast);

		TokenIterator iter = tokens.begin();
		Error error = program_parse(&ast->program, iter);

		return error;
	}

	void ast_free(Ast *self)
	{
		if (!self)
			return;

		program_free(&self->program);
	}
}
