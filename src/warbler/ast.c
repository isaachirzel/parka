#include <warbler/ast.h>

// standard
#include <stdlib.h>

void program_free(Program *program)
{
	// TODO: implement this
	free(program);
}

void module_free(Module *module)
{
	// TODO: implement this
	free(module);
}
void typename_free(Typename *typename)
{
	// TODO: implement this
	free(typename);
}
void identifier_free(Identifier *identifier)
{
	// TODO: implement this
	free(identifier);
}
void function_free(Function *function)
{
	// TODO: implement this
	free(function);
}
void statement_free(Statement *statement)
{
	// TODO: implement this
	free(statement);
}
void expression_free(Expression *expression)
{
	// TODO: implement this
	free(expression);
}
