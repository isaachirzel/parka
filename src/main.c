#include <warbler/file.h>
#include <warbler/preprocessor.h>
#include <warbler/parser.h>
#include <warbler/validator.h>
#include <warbler/util/print.h>

#define SOURCE "function main()\n"\
"{\n"\
"	var i: i32 = 0;\n"\
"	var i: i32 = 1;\n"\
"}\n"
#define FILENAME "file.wb"
#define FILEPATH "src"

int main(void)
{
	File file = fileFrom(FILENAME, SOURCE);
	Directory directory = directoryFrom(FILEPATH, &file);

	ProgramSyntax syntax;

	if (!parse(&syntax, &directory, 1))
		return 1;

	print("Successfully parsed.");

	ProgramContext context;

	if (!validate(&context, &syntax))
		return 2;

	print("Successfully validated.");

	return 0;
}

