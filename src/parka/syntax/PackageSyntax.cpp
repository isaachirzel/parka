#include "parka/syntax/PackageSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/syntax/StructSyntax.hpp"
#include "parka/repository/EntitySyntaxId.hpp"

#include "parka/util/Array.hpp"
#include "parka/file/Directory.hpp"
#include "parka/file/File.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	EntitySyntaxId PackageSyntax::parse(const Directory& directory, const String& name)
	{
		// TODO: Add multithreading
		print("Package `$` has $ subpackages and $ modules", name, directory.subdirectories().length(), directory.files().length());

		auto modules = Array<ModuleSyntax>(directory.files().length());
		auto packageIds = Array<EntitySyntaxId>(directory.subdirectories().length());

		for (const auto& file : directory.files())
			modules.push(ModuleSyntax::parse(file));

		for (const auto& subdirectory : directory.subdirectories())
			packageIds.push(PackageSyntax::parse(subdirectory, subdirectory.name()));

		auto package = PackageSyntax(String(name), std::move(modules), std::move(packageIds));
		auto id = EntitySyntaxId::create(std::move(package));

		return id;
	}

	// bool PackageSyntax::validate()
	// {
	// 	auto success = true;
	// 	auto id = Primitive::getId(*this);

	// 	for (auto& mod : _modules)
	// 	{
	// 		if (!mod.validate(id))
	// 			success = false;
	// 	}

	// 	for (const auto& packageId : _packageIds)
	// 	{
	// 		auto& package = SyntaxRepository::getPackage(packageId);

	// 		if (!package.validate(id))
	// 			success = false;
	// 	}

	// 	return success;
	// }

	// bool PackageSyntax::validate(const EntitySyntaxId& parentPackageId)
	// {
	// 	// TODO: Multithreading
	// 	auto success = true;
	// 	auto id = Primitive::getId(*this);

	// 	for (auto& mod : _modules)
	// 	{
	// 		if (!mod.validate(id))
	// 			success = false;
	// 	}

	// 	for (const auto& packageId : _packageIds)
	// 	{
	// 		auto& package = SyntaxRepository::getPackage(packageId);

	// 		if (!package.validate(id))
	// 			success = false;
	// 	}

	// 	return success;
	// }
}
