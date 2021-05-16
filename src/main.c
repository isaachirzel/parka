// local includes
#include <grackle/lex.h>
#include <grackle/defs.h>
#include <grackle/preprocessor.h>

// standard library
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// external libraries
#define HIRZEL_UTIL_FILE_I
#include <hirzel/util/file.h>

void print_stringview(StringView view)
{
	for (uint16_t i = 0; i < view.len; ++i)
	{
		putchar(view.ptr[i]);
	}
	putchar('\n');
}

int main(void)
{
	// reading src
	String src = hxfile_read_text("./test/file.gx");
	puts("Raw:  ==================");
	puts(src);
	preprocess(src);
	puts("Preprocessed:  =========");
	puts(src);
	
	// // lexing file
	// puts("INIT");
	// lex_init();
	// puts("INIT");
	// toklist_t *toks = lex(src);


	// printf("Size of toks: %zu\n", toks->len);

	// for (size_t i = 0; i < toks->len; ++i)
	// {
	// 	token_t *tok = toklist_getr(toks, i);
	// 	print_stringview(tok->str);
	// }


	// toklist_destroy(toks);
	// lex_cleanup();
	free(src);
	return 0;
}
