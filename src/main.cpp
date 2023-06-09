#include "parka/context/ContextTree.hpp"
#include "parka/syntax/SyntaxTree.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Timer.hpp"

#include "parka/log/ArenaStreamBuffer.hpp"

using namespace parka;

// TODO: Unit testing
// TODO: Convert log fatals to exceptions and add catch that will print out a single log fatal

int main(int argc, const char *argv[])
{
	if (argc != 2)
		log::fatal("Please supply only a path to the project root directory.");

	auto timer = Timer();
	auto project = Project::read(argv[1]);
	auto readTime = timer.split();

	log::note("Project loaded in $ seconds.", readTime);

	auto syntax = SyntaxTree::parse(project);
	auto parseTime = timer.split();

	log::note("Parsing completed in $s.", parseTime);

	auto context = ContextTree::validate(syntax);
	auto validateTime = timer.split();

	log::note("Validation completed in $s.", validateTime);

	auto errorCount = log::getErrorCount();
	auto compileTime = timer.stop();
	auto linesOfCodeCount = project.getLinesOfCodeCount();
	auto compileSpeed = (usize)(linesOfCodeCount / compileTime / 1000.0);

	if (errorCount > 0)
	{
		log::fatal("Failed to compile `$`: encountered $ error(s).", project.name(), errorCount);
	}
	else
	{
		log::success("Compiled `$` in $ seconds at $k lines/s.", project.name(), compileTime, compileSpeed);
	}
}
