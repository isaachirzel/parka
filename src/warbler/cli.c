#include <warbler/cli.h>

// local includes
#include <warbler/print.h>

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
		error("invalid arguments given");
		print_help();

		return false;
	}

	return true;
}
