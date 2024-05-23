#include "parka/evaluation/Evaluator.hpp"
#include "parka/log/Log.hpp"
#include "parka/parser/ParkaParser.hpp"
#include "parka/util/Timer.hpp"
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

	log::debug("Project loaded in $ seconds.", readTime);

	auto ast = parser::parse(project);
	auto parseTime = timer.split();

	log::debug("Parsing completed in $s.", parseTime);

	auto ir = validator::validateAst(ast);
	auto validateTime = timer.split();

	log::debug("Validation completed in $s.", validateTime);

	auto errorCount = log::getErrorCount();
	auto compileTime = timer.stop();
	auto linesOfCodeCount = project.getLinesOfCodeCount();
	auto compileSpeed = (usize)(linesOfCodeCount / compileTime / 1000.0);

	if (errorCount > 0)
	{
		log::fatal("Failed to compile `$`: encountered $ error(s).", project.name(), errorCount);
		return 1;
	}
	
	log::success("Compiled `$` in $ seconds at $k lines/s.", project.name(), compileTime, compileSpeed);

	evaluation::evaluate(*ir);

	auto evaluateTime = timer.split();
	log::debug("Evaluation completed in $s.", evaluateTime);
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

*/

/*
	RESOLVABLE PROTOTYPES TYPES
	FUNCTION OPERATORS should fix the problem with setting the body on a functions.
	When resolving the prototype, it doesn't need to be executed at all, it just needs the type 
	to be resolved
	This 
	Maybe having the prototype TypeIr as part of the function entry is a good idea?
	I'm not sure how setting the function ir in the identifier expression afterwards will work?
*/
