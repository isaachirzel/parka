// local includes
#include <grackle/lex.h>
#include <grackle/string.h>
#include <grackle/preprocessor.h>

// standard library
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// external libraries
#define HIRZEL_UTIL_FILE_I
#include <hirzel/util/file.h>

void print_stringview(String view)
{
	for (unsigned i = 0; i < view.len; ++i)
	{
		putchar(view.ptr[i]);
	}
}

int main(void)
{
	// reading src
	char *src = hxfile_read_text("./test/file.gx");
	preprocess(src);
	puts(src);
	
	// lexing file
	lex_init();
	toklist_t *toks = lex(src);

	printf("Size of toks: %zu\n\n", toks->len);

	for (size_t i = 0; i < toks->len; ++i)
	{
		token_t *tok = toklist_get_ref(toks, i);
		print_stringview(tok->str);
		printf("\t%d\n", (int)tok->type);
	}


	toklist_destroy(toks);
	lex_cleanup();
	free(src);
	return 0;
}
