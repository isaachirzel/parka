#ifndef GENERATOR_H
#define GENERATOR_H

// local includes
#include <grackle/data/node.h>
#include <grackle/data/scope.h>
#include <grackle/container/strlist.h>

// standard library
#include <stdio.h>

extern strlist_t *generate(const node_t * const node);
extern char *generate_mangled_symbol(const string_t * const ident,
	const scope_t * const scope);
extern void generate_print(strlist_t * gen);
#endif
