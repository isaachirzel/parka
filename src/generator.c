// header
#include <grackle/generator.h>

// local includes
#include <grackle/container/strlist.h>

// standard library
#include <grackle/assert.h>

function_t generate_function(const node_t *node)
{
	ASSERT(node->type == NODE_FUNCTION);
	// example mangling offunction
	/*
		// in util.gx
		func add(a: i32, b: i32) -> i32

		// in main.gx
		util::add(4, 5);

		gets mangled to:
		func_util_add(4, 5);
		
	*/

	size_t headerc = 0;
	
}

/*
type string: struct
{
	data: char[]
	len: uword
}

implement for string
{
	func push(c: char)
	{
	}
}
*/

module_t generate_module(const node_t *node)
{
	// creating return data
	module_t out =
	{
		strlist_create(),
		malloc(node->argc * sizeof(component_t)),
		node->argc
	};
	// verifying data
	if (!out.decl || !out.comps) return out;

	for (size_t i = 0; i < out.compc; ++i)
	{
		const node_t *arg = node->args[i];
		component_t *comp = out.comps + i;

		switch (arg->type)
		{
		case NODE_FUNCTION:
			comp->type = COMPONENT_FUNC;
			comp->data.func = generate_function(arg);
			break;

		}
	}

	return out;
}


module_t generate(const node_t *node)
{
	return generate_module(node);
}


void generate_print(strlist_t *gen)
{
	for (size_t i = 0; i < gen->len; ++i)
	{
		fputs(strlist_get(gen, i), stdout);
	}
}
