#include <warbler/parser.h>
#include <warbler/util/memory.h>
#include <warbler/util/path.h>
#include <warbler/util/file.h>
#include <warbler/util/print.h>
#include <warbler/util/timer.h>
#include <warbler/validator.h>

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

	ClockTimerId timerId = clockTimerStart();
	Project project = projectLoad(argv[1]);

	symbolTableInitialize(project.name);

	if (!parse(&project))
	{
		printErrorCount(&project);
		return 1;
	}

	if (!validate())
	{
		printErrorCount(&project);
		return 2;
	}

	symbolTableDestroy();

	f64 elapsedSeconds = clockTimerStop(timerId);

	printSuccess("compiled `%s` in %f seconds.", project.name, elapsedSeconds);

	return 0;
}
