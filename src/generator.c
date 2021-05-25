// header
#include <grackle/generator.h>

#define generate_func(func) char *generate_##func(node_t *node)


generate_func(function)
{

}


generate_func(program)
{
	for (unsigned i = 0; i < node->argc; ++i)
	{
		generate_function(node->args[i]);
	}
}


char *generate(node_t *node)
{

	switch (node->type)
	{
	case NODE_FUNCTION:
		generate(node->args

		for (unsigned i = 0; i < node->argc; ++i)
		{
			generate(node->args[i]);
		}
		break;

	case NODE_VAR_DECLARATION:

		break;

	case NODE_EXPRESSION:

		break;
	}
}

finch
warbler
gull
puffin
raven
