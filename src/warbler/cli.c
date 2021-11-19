#include <warbler/cli.h>

// standard library
#include <stdio.h>

const char * help_str = "usage: warble <input file>";

void print_help()
{
	printf("%s\n", help_str);
}

bool validate_cli_args(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("error: invalid arguments given\n");
		print_help();
		
		return false;
	}
	return false;
}
