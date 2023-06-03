#include "parka/context/ContextTree.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/log/Color.hpp"
#include "parka/log/Link.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/GlobalSymbolTable.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/SyntaxTree.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/Token.hpp"
#include "parka/file/File.hpp"
#include "parka/util/Path.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/String.hpp"
#include "parka/util/Table.hpp"
#include "parka/util/Timer.hpp"

#include <ios>
#include <type_traits>

using namespace parka;

int main(int argc, const char *argv[])
{
	Log::note("This is log #$", 1);

	KeywordSyntax::initialize();

	if (argc != 2)
		Log::fatal("Please supply only a path to the project root directory.");

	auto timer = Timer();
	auto project = Project::read(argv[1]);
	auto readTime = timer.split();

	Log::success("Project loaded in $ seconds.", readTime);

	auto syntax = SyntaxTree::parse(project);
	auto parseTime = timer.split();

	Log::success("Parsing completed in $s.", parseTime);

	auto symbolTable = GlobalSymbolTable(syntax);
	auto declareTime = timer.split();

	Log::success("Declaration completed in $s.", declareTime);

	// auto context = ContextTree::validate(syntax);
	// auto validateTime = timer.split();

	// Log::success("Validation completed in $s.", validateTime);

	auto errorCount = Log::getErrorCount();
	auto compileTime = timer.stop();
	auto linesOfCodeCount = project.getLinesOfCodeCount();
	auto compileSpeed = (usize)(linesOfCodeCount / compileTime / 1000.0);

	if (errorCount > 0)
	{
		Log::fatal("Failed to compile `$`: encountered $ error(s).", project.name(), errorCount);
	}
	else
	{
		Log::success("Compiled `$` in $ seconds at $k lines/s.", project.name(), compileTime, compileSpeed);
	}

	Log::outputEntries();
}
