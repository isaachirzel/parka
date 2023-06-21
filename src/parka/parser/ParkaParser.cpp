#include "parka/parser/ParkaParser.hpp"
#include "parka/parser/ParkaFileParser.hpp"

using namespace parka::ast;

namespace parka::parser
{
	static PackageAst *parsePackage(const Directory& directory, const String& name)
	{
		// TODO: Add multithreading
		auto modules = Array<ModuleAst>(directory.files().length());
		auto packages = Array<PackageAst*>(directory.subdirectories().length());

		for (const auto& file : directory.files())
		{
			auto parser = ParkaFileParser(file);

			modules.push(parser.parse());
		}

		for (const auto& subdirectory : directory.subdirectories())
			packages.push(parsePackage(subdirectory, subdirectory.name()));

		auto *syntax = new PackageAst(String(name), std::move(modules), std::move(packages));

		return syntax;
	}

	Ast ParkaParser::parse()
	{
		// TODO: Parse external projects
		auto *package = parsePackage(_project.srcDirectory(), "");

		assert(package != nullptr);

		auto result = Ast(*package);

		return result;
	}
}
