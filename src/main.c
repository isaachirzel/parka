#include "parka/util/table.h"
#include "parka/parser.h"
#include "parka/util/memory.h"
#include "parka/util/path.h"
#include "parka/util/file.h"
#include "parka/util/print.h"
#include "parka/util/timer.h"
#include "parka/validator.h"

void printErrorCount(Project *project)
{
	usize errorCount = getErrorCount();

	assert(errorCount > 0);

	printError("Failed to compile `%s`: encountered %zu error(s).", project->name, errorCount);
}

int main(int argc, const char *argv[])
{
	if (argc != 2)
		exitWithError("Please supply only a path to the project root directory.");

	ClockTimerId compileTimerId = clockTimerStart();
	Project project = projectLoad(argv[1]);

	symbolTableInitialize(project.name);

	printNote("starting parsing");

	if (!parse(&project))
	{
		printErrorCount(&project);
		return 1;
	}

	printSuccess("parsing complete");
	printNote("starting validating");

	if (!validate())
	{
		printErrorCount(&project);
		return 2;
	}

	printSuccess("validation complete");
	printNote("generation not implemented yet");

	symbolTableDestroy();

	f64 compilationDuration = clockTimerStop(compileTimerId);

	printSuccess("compiled `%s` in %f seconds.", project.name, compilationDuration);

	return 0;
}
