#include "parka/ast/Ast.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/log/Log.hpp"
#include "parka/parser/ParkaParser.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/Timer.hpp"
#include "parka/log/ArenaStreamBuffer.hpp"
#include "parka/validator/Validator.hpp"

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

	auto ast = parser::ParkaParser(project).parse();
	auto parseTime = timer.split();

	log::note("Parsing completed in $s.", parseTime);

	// auto validator = validator::Validator(ast);
	// auto declareTime = timer.split();

	// log::note("Declaration completed in $s.", declareTime);

	// print("$\n", syntax);

	auto ir = validator::validateAst(ast);
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

/*
validation lock:

	auto readLock = shared_lock(mutex);

	if (validated)
		return context;

	readLock.unlock();

	auto writeLock = unique_lock(mutex, std::defer_lock_t);

	if (writeLock.try_lock())
	{
		context = syntax.validate(symbolTable);
		validated = true;

		return context;
	}


	// Here is where 

	while (!readLock.try_lock())
	{
		// Do something else to not waste time
		// Defer the coroutine?
	}

	return context;


Thing:

	+ declaration uses temporary state and does not modify tree

	+ walking 

	declaration would have the 

	Validator
		PackageSymbolTable[]
*/




