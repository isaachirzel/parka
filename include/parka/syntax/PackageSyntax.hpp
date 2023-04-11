#ifndef PARKA_SYNTAX_PACKAGE_SYNTAX_HPP
#define PARKA_SYNTAX_PACKAGE_SYNTAX_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/data/EntitySyntax.hpp"
#include "parka/data/EntityId.hpp"
#include "parka/Token.hpp"
#include "parka/util/Array.hpp"
#include "parka/file/Directory.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Project.hpp"

#include <stdexcept>

namespace parka
{
	class PackageSyntax : public EntitySyntax
	{
		String _identifier;
		Array<ModuleSyntax> _modules;
		Array<EntityId> _packageIds;
		// Validation

		PackageSyntax(Array<EntityId>&& packageIds) :
		_identifier(),
		_modules(),
		_packageIds(std::move(packageIds))
		{}

		PackageSyntax(String&& identifier, Array<ModuleSyntax>&& modules, Array<EntityId>&& packageIds) :
		_identifier(std::move(identifier)),
		_modules(std::move(modules)),
		_packageIds(std::move(packageIds))
		{}

		static Optional<EntityId> parse(const Directory& directory, const String& name);
		
	public:

		PackageSyntax(PackageSyntax&&) = default;
		PackageSyntax(const PackageSyntax&) = delete;
		~PackageSyntax() = default;

		static Optional<EntityId> parse(const Project& project);

		const String& identifier() const { return _identifier; }
		EntityType type() const { return EntityType::PackageSyntax; }
		const auto& modules() const { return _modules; }
		const auto& packageIds() const { return _packageIds; }
	};
}

#endif
