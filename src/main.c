// local includes
#include <warbler/file.h>
#include <warbler/cli.h>
#include <warbler/preprocessor.h>
#include <warbler/tokenizer.h>

// standard library
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (!validate_cli_args(argc, argv))
		return 1;

	char *src = read_file(argv[1]);

	preprocess(src);
	printf("success:\n%s\n", src);

	Tokenizer tokenizer;

	auto tokens = tokenizer.tokenize(src);

	free(src);
	return 0;
}

