#include "parka/context/ContextTree.hpp"
#include "parka/syntax/SyntaxTree.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Print.hpp"
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

	syntax.declareSelf();
	auto declareTime = timer.split();

	log::note("Declaration completed in $s.", declareTime);

	print("$\n", syntax);

	auto context = syntax.validate();
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
validating function and struct at same time
struct is not fnished
function needs to validate struct
function goes to symbol table and finds struct

then:

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


funtion checks if struct is being validated
if it's not being validated, validate it
if it is, wait for it to be finished then get the value

symbol table separate from entity: -1

	+ declaration produces an encapsulated object

	- walking table doesn't work well as they can't be sorted by type (cache miss)
		and only non duplicate entities will be validated

	- validation required passing symbol table to every function and updating
		tree's parents which is not easy to accomplish while keeping code clean

symbol table inside entity: 0

	/ declaration modifies syntax tree

	+ walking the table is easy because all entities will be validated in order

	- validation requires updating parents of tree to point to the table
		which will make it impossible to have the symbol table know what
		entity it is associated with without duplicating data

symbol table is entity: 2

	/ declaration modifies syntax tree

	+ walking the table is easy because all entities will be validated in order

	+ validation requires updating parents of the entities but there is no 
		tossup or potential for data duplication

*/

