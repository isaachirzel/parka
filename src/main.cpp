#include "parka/syntax/SyntaxTree.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/repository/Storage.hpp"
#include "parka/Token.hpp"
#include "parka/file/File.hpp"
#include "parka/util/Path.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/String.hpp"
#include "parka/util/Table.hpp"
#include "parka/util/Timer.hpp"

using namespace parka;

void printErrorCount(const Project& project)
{
	printError("Failed to compile `$`: encountered $ error(s).", project.name(), getErrorCount());
}

int main(int argc, const char *argv[])
{
	Storage::initialize();

	if (argc != 2)
		exitWithError("Please supply only a path to the project root directory.");

	auto timer = Timer();
	auto project = Project::read(argv[1]);

	if (!project)
		return 1;

	auto readTime = timer.split();

	printSuccess("Project loaded in $ seconds.", readTime);

	auto ast = SyntaxTree::parse(*project);

	if (!ast)
	{
		printErrorCount(*project);
		return 1;
	}

	auto parseTime = timer.split();

	printSuccess("Parsing completed in $ seconds.", parseTime);

	// if (!ast->validate())
	// {
	// 	printErrorCount(*project);
	// 	return 1;
	// }

	// auto validatetime = timer.split();

	// printSuccess("Validation completed in $ seconds.", validatetime);

	auto compileTime = timer.stop();
	auto linesOfCodeCount = project->getLinesOfCodeCount();
	auto compileSpeed = (usize)(linesOfCodeCount / compileTime / 1000.0);

	printSuccess("Compiled `$` in $ seconds at $k lines/sec.", project->name(), compileTime, compileSpeed);

	return 0;
}
