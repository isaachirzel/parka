// local includes
#include <grackle/lexer.h>
#include <grackle/string.h>
#include <grackle/preprocessor.h>

// standard library
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// external libraries
#define HIRZEL_UTIL_FILE_I
#include <hirzel/util/file.h>

int main(void)
{
	// reading src
	char *src = hxfile_read_text("./test/file.gx");
	preprocess(src);
	puts(src);
	puts("====================================");
	// lexing file
	lex_init();
	toklist_t *toks = lex(src);

	printf("Size of toks: %zu\n\n", toks->len);

	for (size_t i = 0; i < toks->len; ++i)
	{
		token_t *tok = toklist_get_ref(toks, i);
		string_print(tok->str);
		printf("\ttype %d\tline: %u\tcol: %u\n", (int)tok->type, tok->line, tok->col);
	}


	toklist_destroy(toks);
	lex_cleanup();
	free(src);
	return 0;
}
