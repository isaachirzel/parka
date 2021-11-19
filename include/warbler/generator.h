#ifndef GENERATOR_H
#define GENERATOR_H

// local includes
#include <grackle/data/node.h>
#include <grackle/data/scope.h>
#include <grackle/container/strlist.h>

// standard library
#include <stdio.h>


typedef struct function
{
	char *decl;
	strlist_t *def;
} function_t;

typedef struct import
{
	const string_t *id;
	const string_t *alias;
} import_t;

typedef struct type
{

	char *def;

} type_t;


#define COMPONENT_FUNC 0
#define COMPONENT_IMPORT 1
#define COMPONENT_TYPE 2

typedef struct component
{
	char type;
	union
	{
		import_t import;
		string_t type;
		function_t func;
	} data;
} component_t;
	

typedef struct module
{
	strlist_t *decl; // to store needed
	component_t *comps;
	size_t compc;
} module_t;

extern module_t generate(const node_t * node);
#endif
