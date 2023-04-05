#include "parka/ast/ast.hpp"
#include "parka/node/entity_id.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/token.hpp"
#include "parka/util/file.hpp"
#include "parka/util/path.hpp"
#include "parka/util/print.hpp"
#include "parka/util/string.hpp"
#include "parka/util/table.hpp"
#include "parka/util/timer.hpp"

void printErrorCount(const Project& project)
{
	printError("Failed to compile `$`: encountered $ error(s).", project.name(), getErrorCount());
}

int main(int argc, const char *argv[])
{
	NodeBank::initialize();

	if (argc != 2)
		exitWithError("Please supply only a path to the project root directory.");

	auto timer = Timer();
	auto project = Project::read(argv[1]);

	if (!project)
		return 1;

	auto readTime = timer.split();

	printSuccess("Project loaded in $ seconds.", readTime);

	auto ast = Ast::parse(*project);

	if (!ast)
	{
		printErrorCount(*project);
		return 1;
	}

	auto parseTime = timer.split();

	printSuccess("Parsing completed in $ seconds.", parseTime);

	if (!ast->validate())
	{
		printErrorCount(*project);
		return 1;
	}

	auto validatetime = timer.split();

	printSuccess("Validation completed in $ seconds.", validatetime);

	auto compileTime = timer.stop();
	auto linesOfCodeCount = project->getLinesOfCodeCount();
	auto compileSpeed = (usize)(linesOfCodeCount / compileTime / 1000.0);

	printSuccess("Compiled `$` in $ seconds at $k lines/sec.", project->name(), compileTime, compileSpeed);

	return 0;
}
