#include "parka/ast/package.hpp"
#include "parka/util/project.hpp"

bool parse(const Project *project)
{
	// TODO: Only allow qulified ids for symbols and unqualified ids for declarations
	Scope package = { 0 };

	bool success = parsePackage(&project->srcDir, &package, project->name);

	scopeDestroy(&package);

	return success;
}
