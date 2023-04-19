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
	Optional<EntitySyntaxId> PackageSyntax::parse(const Directory& directory, const String& name)
	{
		// TODO: Add multithreading
		print("Package `$` has $ subpackages and $ modules", name, directory.subdirectories().length(), directory.files().length());
		auto success = true;
		auto modules = Array<ModuleSyntax>();
		auto packageIds = Array<EntitySyntaxId>(directory.subdirectories().length());

		for (const auto& file : directory.files())
		{
			auto mod = ModuleSyntax::parse(file);

			if (!mod)
			{
				success = false;
				continue;
			}

			modules.push(*mod);
		}

		for (const auto& subdirectory : directory.subdirectories())
		{
			auto packageId = PackageSyntax::parse(subdirectory, subdirectory.name());

			if (!packageId)
			{
				success = false;
				continue;
			}

			packageIds.push(*packageId);
		}

		if (!success)
			return {};

		auto package = PackageSyntax(String(name), std::move(modules), std::move(packageIds));
		auto id = EntitySyntaxId::create(std::move(package));

		return id;
	}

	Optional<EntitySyntaxId> PackageSyntax::parse(const Project& project)
	{
		return PackageSyntax::parse(project.srcDirectory(), "");
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
