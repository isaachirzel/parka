#include "parka/entity/node_bank.hpp"
#include "parka/util/string.hpp"
#include "parka/util/table.hpp"
#include "parka/ast/ast.hpp"

#include "parka/util/path.hpp"
#include "parka/util/file.hpp"
#include "parka/util/print.hpp"
#include "parka/util/timer.hpp"

#include <iostream>

void printErrorCount(Project& project)
{
	usize errorCount = getErrorCount();

	assert(errorCount > 0);

	std::cout << "Failed to compile `" << project.name() << "`: encountered " << errorCount << " error(s)." << std::endl;
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
	
	printNote("starting parsing");

	auto astResult = Ast::parse(project);


	if (!astResult)
	{
		printErrorCount(project);
		return 1;
	}

	auto& ast = astResult.value();

	printSuccess("parsing complete");
	printNote("starting validating");

	if (!ast.validate())
	{
		printErrorCount(project);
		return 1;
	}

	printSuccess("validation complete");
	printNote("generation not implemented yet");

	compileTimer.stop();

	printSuccess("compiled `%s` in %f seconds.", project.name().c_str(), compileTimer.elapsedSeconds());

	return 0;
}
