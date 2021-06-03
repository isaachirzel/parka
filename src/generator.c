// header
#include <grackle/generator.h>

// local includes
#include <grackle/container/strlist.h>

// standard library
#include <grackle/assert.h>

#define generate_func(func) char *generate_##func(node_t *node)


char *generate_mangled_symbol(const string_t * const ident,
	const scope_t * const scope)
{
	return NULL;
}

void generate_identifier(const node_t *node, strlist_t *out)
{
	// string_fputs(&node->val->str, out);
}

void generate_typename(const node_t *node, strlist_t *out)
{
	ASSERT(node->type == NODE_TYPENAME);
	printf("Type: %u\n", node->val->type);
	// check 
	switch (node->val->type)
	{
	case TOK_TYPE_I8:
		// fputs("int8_t ", out);
		break;

	case TOK_TYPE_I16:
		// fputs("int16_t ", out);
		break;

	case TOK_TYPE_I32:
		// fputs("int32_t ", out);
		break;

	case TOK_TYPE_I64:
		// fputs("int64_t ", out);
		break;

	case TOK_TYPE_U8:
		// fputs("uint8_t ", out);
		break;

	case TOK_TYPE_U16:
		// fputs("uint16_t ", out);
		break;

	case TOK_TYPE_U32:
		// fputs("uint32_t ", out);
		break;

	case TOK_TYPE_U64:
		// fputs("uint64_t ", out);
		break;

	case TOK_TYPE_F32:
		// fputs("float ", out);
		break;

	case TOK_TYPE_F64:
		// fputs("double ", out);
		break;

	case TOK_TYPE_STR:
		// fputs("const char *", out);
		break;

	case TOK_IDENTIFIER:
		// string_fputs(&node->val->str, out);
		break;
	}
}

void generate_declaration(const node_t *node, strlist_t *out)
{
	ASSERT(node->type == NODE_DECL_STMT);
	generate_typename(node->args[1], out);
	generate_identifier(node->args[0], out);
}


void generate_statement(const node_t *node, strlist_t *out)
{
	switch (node->type)
	{
	case NODE_DECL_STMT:
		generate_declaration(node, out);
		break;

	case NODE_COMPOUND_STMT:
		// fputs("{\n", out);
		for (unsigned i = 0; i < node->argc; ++i)
		{
			generate_statement(node->args[i], out);
		}
		// fputs("}", out);
		break;

	default:;
	}
	// fputs("\n", out);
}


void generate_arglist(const node_t *node, strlist_t *out)
{

}


void generate_function(const node_t *node, strlist_t *out)
{
	ASSERT(node->type == NODE_FUNCTION);
	generate_typename(node->args[2], out);
	generate_identifier(node->args[0], out);
	generate_arglist(node->args[1], out);
	generate_statement(node->args[3], out);
}


void generate_program(const node_t *node, strlist_t *out)
{
	ASSERT(node->type == NODE_PROGRAM);
	for (unsigned i = 0; i < node->argc; ++i)
	{
		generate_function(node->args[i], out);
	}
}


strlist_t *generate(const node_t *node)
{
	strlist_t *out = strlist_create();
	generate_program(node, out);

	return out;
}


void generate_print(strlist_t *gen)
{
	for (size_t i = 0; i < gen->len; ++i)
	{
		fputs(strlist_get(gen, i), stdout);
	}
}
