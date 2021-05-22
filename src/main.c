// local includes
#include <grackle/string.h>
#include <grackle/preprocessor.h>
#include <grackle/lexer.h>
#include <grackle/parser.h>

// standard library
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// external libraries
#define HIRZEL_UTIL_FILE_I
#include <hirzel/util/file.h>

void print_toks(toklist_t *toks)
{
	printf("Size of toks: %zu\n\n", toks->len);

	for (size_t i = 0; i < toks->len; ++i)
	{
		token_t *tok = toklist_get_ref(toks, i);
		string_print(tok->str);
		printf("\ttype %d\tline: %u\tcol: %u\n", (int)tok->type, tok->line, tok->col);
	}
}

int main(void)
{
	// reading src
	char *src = hxfile_read_text("./test/file.gx");
	// preprocessing src
	preprocess(src);

	// printing src
	// puts(src);

	// lexing src
	lex_init();
	toklist_t *toks = lex(src);

	// pritning toks
	// print_toks(toks);

	// parsing src
	node_t *ast = parse(toks);

	// memory cleanup
	node_destroy(ast);
	toklist_destroy(toks);
	lex_cleanup();
	free(src);
	return 0;
}
