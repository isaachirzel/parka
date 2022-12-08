#include <warbler/util/file.h>
#include <warbler/parser.h>
#include <warbler/validator.h>
#include <warbler/util/print.h>

int main(int argc, const char *argv[])
{
	if (argc != 2)
		exitWithError("Please supply only path to src folder");

	Project project = projectLoad(argv[1]);

	symbolTableInitialize(project.name);

	if (!parse(&project))
		return 1;

	print("Successfully parsed.");

	if (!validate())
		return 2;

	print("Successfully validated.");

	symbolTableDestroy();

	return 0;
}
