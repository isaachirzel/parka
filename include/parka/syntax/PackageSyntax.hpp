#ifndef PARKA_SYNTAX_PACKAGE_SYNTAX_HPP
#define PARKA_SYNTAX_PACKAGE_SYNTAX_HPP

#include "parka/context/PackageContext.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/Token.hpp"
#include "parka/util/Array.hpp"
#include "parka/file/Directory.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Project.hpp"

namespace parka
{
	class PackageSyntax : public EntitySyntax
	{
		String _identifier;
		Array<ModuleSyntax> _modules;
		Array<PackageSyntax*> _packages;

	public:

		PackageSyntax(String&& identifier, Array<ModuleSyntax>&& modules, Array<PackageSyntax*>&& packages);
		PackageSyntax(PackageSyntax&&) = default;
		PackageSyntax(const PackageSyntax&) = delete;

		static PackageSyntax *parse(const Directory& directory, const String& name);

		PackageContext *validate(SymbolTable& symbolTable);

		EntityType entityType() const { return EntityType::Package; }
		const String& identifier() const { return _identifier; }
		const auto& modules() const { return _modules; }
		const auto& packages() const { return _packages; }
	};
}

#endif
