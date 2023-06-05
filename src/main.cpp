#include "parka/symbol/GlobalSymbolTable.hpp"
#include "parka/syntax/SyntaxTree.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Timer.hpp"

#include "parka/log/ArenaStreamBuffer.hpp"

using namespace parka;

// TODO: Unit testing

int main(int argc, const char *argv[])
{
	auto buffer = ArenaStreamBuffer(1 << 30);
	auto stream = std::ostream(&buffer);

	stream << 1;
	stream << ' ' << "Hello :)";

	log::note("This is log #$", 1);

	if (argc != 2)
		log::fatal("Please supply only a path to the project root directory.");

	auto timer = Timer();
	auto project = Project::read(argv[1]);
	auto readTime = timer.split();

	log::success("Project loaded in $ seconds.", readTime);

	auto syntax = SyntaxTree::parse(project);
	auto parseTime = timer.split();

	log::success("Parsing completed in $s.", parseTime);

	auto symbolTable = GlobalSymbolTable(syntax);
	auto declareTime = timer.split();

	log::success("Declaration completed in $s.", declareTime);

	std::cout << '\n' << symbolTable << "\n\n";
	// auto context = ContextTree::validate(syntax);
	// auto validateTime = timer.split();

	// log::success("Validation completed in $s.", validateTime);

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

	// TODO: Figure out better method for outputting log
	// log::outputEntries();
}
