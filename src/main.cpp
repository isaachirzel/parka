#include "parka/symbol/entity_id.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/token.hpp"
#include "parka/util/string.hpp"
#include "parka/util/table.hpp"
#include "parka/ast/ast.hpp"

#include "parka/util/path.hpp"
#include "parka/util/file.hpp"
#include "parka/util/print.hpp"
#include "parka/util/timer.hpp"

#include <iostream>
#include <stdexcept>

void printErrorCount(Project& project)
{
	printError("Failed to compile `$`: encountered $ error(s).", project.name(), getErrorCount());
}

int main(int argc, const char *argv[])
{
	NodeBank::initialize();

	if (argc != 2)
		exitWithError("Please supply only a path to the project root directory.");

	auto compileTimer = Timer();

	compileTimer.start();

	auto projectResult = Project::read(argv[1]);

	if (!projectResult)
		return 1;

	auto& project = projectResult.value();

	printNote("Parsing begin.");

	auto astResult = Ast::parse(project);

	if (!astResult)
	{
		printErrorCount(project);
		return 1;
	}

	auto& ast = astResult.value();

	printSuccess("Parsing complete.");
	printNote("Validation begin.");

	if (!ast.validate())
	{
		printErrorCount(project);
		return 1;
	}

	printSuccess("Validation complete.");
	printNote("Generation not implemented yet.");

	compileTimer.stop();

	printSuccess("Compiled `$` in $ seconds.", project.name(), compileTimer.elapsedSeconds());

	return 0;
}
