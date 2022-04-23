#include <warbler/cli.hpp>

// local includes
#include <warbler/util/print.hpp>

namespace warbler
{
	const char * help_str = "usage: warble <input file>";

	void print_help()
	{
		printf("%s\n", help_str);
	}

	// bool validate_cli_args(int argc, char *argv[])
	// {
	// 	if (argc != 2)
	// 	{
	// 		error_out() << "invalid arguments given";
	// 		print_help();

	// 		return false;
	// 	}


	// 	return true;
	// }
}
