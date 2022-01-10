#include <warbler/cli.hpp>

// local includes
#include <warbler/print.hpp>

namespace warbler
{
	const char * help_str = "usage: warble <input file>";

	void print_help()
	{
		printf("%s\n", help_str);
	}

	bool validate_cli_args(int argc, char *argv[])
	{
		if (argc != 2)
		{
			errorm("invalid arguments given");
			print_help();

			return false;
		}

		return true;
	}
}
