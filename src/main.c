#include <warbler/file.h>
#include <warbler/parser.h>
#include <warbler/validator.h>
#include <warbler/util/print.h>

int main(int argc, const char *argv[])
{
	if (argc != 2)
		exitWithError("Please supply only path to src folder");

	Directory projectDir = directoryRead(argv[1]);
	Directory *srcDir = directoryGetSrcDir(&projectDir);

	if (!srcDir)
	{
		printError("Unable to find 'src' directory.");
		return 1;
	}

	symbolTableInitialize();

	if (!parse(srcDir))
		return 1;

	print("Successfully parsed.");

	if (!validate())
		return 2;

	print("Successfully validated.");

	symbolTableDestroy();

	return 0;
}
