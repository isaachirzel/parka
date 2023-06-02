#ifndef PARKA_SYNTAX_PACKAGE_SYNTAX_HPP
#define PARKA_SYNTAX_PACKAGE_SYNTAX_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
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
		Array<EntitySyntaxId> _packageIds;

		PackageSyntax(Array<EntitySyntaxId>&& packageIds) :
		_identifier(),
		_modules(),
		_packageIds(std::move(packageIds))
		{}

		PackageSyntax(String&& identifier, Array<ModuleSyntax>&& modules, Array<EntitySyntaxId>&& packageIds) :
		_identifier(std::move(identifier)),
		_modules(std::move(modules)),
		_packageIds(std::move(packageIds))
		{}

		static EntitySyntaxId parse(const Directory& directory, const String& name);
		
	public:

		PackageSyntax(PackageSyntax&&) = default;
		PackageSyntax(const PackageSyntax&) = delete;

		static EntitySyntaxId parse(const Project& project);

		const String& identifier() const { return _identifier; }
		EntityType type() const { return EntityType::Package; }
		const auto& modules() const { return _modules; }
		const auto& packageIds() const { return _packageIds; }
	};
}

#endif
