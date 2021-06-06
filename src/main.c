// local includes
#include <grackle/data/string.h>
#include <grackle/preprocessor.h>
#include <grackle/lexer.h>
#include <grackle/parser.h>
#include <grackle/analyzer.h>
#include <grackle/generator.h>
#include <grackle/log.h>

// standard library
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// external libraries
#include <hirzel/util/file.h>


void print_toks(toklist_t *toks)
{
	printf("Size of toks: %zu\n\n", toks->len);

	for (size_t i = 0; i < toks->len; ++i)
	{
		token_t *tok = toklist_getref(toks, i);
		string_print(&tok->str);
		printf("\ttype %d\tline: %u\tcol: %u\n", (int)tok->type, tok->line, tok->col);
	}
}


int main(void)
{
	const char *filepath = "./test/file.gx";
	log_set_filepath(filepath);
	// reading src
	char *src = hxfile_read(filepath);
	// preprocessing src
	preprocess(src);

	// printing src
	// puts(src);

	// lexing src
	lex_init();
	toklist_t *toks = lex(src);
	if (!toks) return 1;
	// pritning toks
	// print_toks(toks);

	// parsing src
	node_t *ast = parse(toks);
	if (!ast) goto cleanup;
	
	puts("\nAbstract Syntax Tree:");
	node_print(ast);

	puts("\n");
	// semantic analysis
	//if (!analyze(ast)) goto cleanup;

	// code generation
	// strlist_t *gen = generate(ast);
	// generate_print(gen);


cleanup:
	// memory cleanup
	node_destroy(ast);
	toklist_destroy(toks);
	lex_cleanup();
	free(src);
	return 0;
}
