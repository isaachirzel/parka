#include <warbler/file.h>
#include <warbler/preprocessor.h>
#include <warbler/parser.h>
#include <warbler/validator.h>
#include <warbler/util/print.h>

#define BAR "\n###########################################################\n"

#define SOURCE ""
#define FILENAME "file.wb"
#define FILEPATH "src"

int main(void)
{
	File file = fileFrom(SOURCE, FILENAME);
	Directory directory = directoryFrom(FILEPATH, &file);

	ProgramSyntax syntax;

	if (!parse(&syntax, &directory, 1))
		return 1;

	ProgramContext context;

	if (!validate(&context, &syntax))
		return 2;

	print("Successfully parsed.");

	return 0;
}

