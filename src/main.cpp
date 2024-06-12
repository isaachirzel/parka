#include "parka/evaluation/Evaluator.hpp"
#include "parka/log/Log.hpp"
#include "parka/parser/ParkaParser.hpp"
#include "parka/util/Timer.hpp"
#include "parka/validation/Validator.hpp"

using namespace parka;

// wordcount: git ls-files | xargs wc -l

// TODO: Unit testing
// TODO: Convert log fatals to exceptions and add catch that will print out a single log fatal

// int main()
// {
// }

i32 main(int argc, const char *argv[])
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

	auto ir = validation::validateAst(ast);
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

	auto exitCode = evaluation::evaluate(*ir);

	auto evaluateTime = timer.split();
	log::debug("Evaluation completed in $s.", evaluateTime);

	return exitCode;
}



/*
	RESOLVABLE PROTOTYPES TYPES
	FUNCTION OPERATORS should fix the problem with setting the body on a functions.
	When resolving the prototype, it doesn't need to be executed at all, it just needs the type 
	to be resolved
	This 
	Maybe having the prototype TypeIr as part of the function entry is a good idea?
	I'm not sure how setting the function ir in the identifier expression afterwards will work?
*/

/*
	unique types for functions are needed add they need to be able to be passed in as arguments
	i need to create a new class such as Signature that will be the type
	the signature will need to be able to be given a
*/

/*
	getConversion will be moved to ExpressionContext
	conversions can replace the validateDefault value in that type() will return default value
		but conversion will allow for more nuance, like integer-> i64 or u8 etc
	

*/

/*
	operators are gotten per type
	prototype is the type of a function

	function has a list of types?
	these types then have references into the type table to get the operators
	calloperators are the function implementations essentially
	conversions should not be on types? or maybe they should?
*/

/*
	in c++, functions are by default handled as overloads, they have candidates even
	if there is only one function implementation for the symbol. This gives functions a flexible type

	Function pointers have a definite type and the error is more "this argument is invalid because of this."

	Conversions to function pointers eventually need to be handled ? This should be resolved similarly to fucntion calls

	Structs with call operators are handled like functions with flexible types

	I honeslty thing that I should handle functions as overloads only if there are more than 1 overload
*/

