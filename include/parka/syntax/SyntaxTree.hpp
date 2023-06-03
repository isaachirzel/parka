#ifndef PARKA_SYNTAX_AST_SYNTAX_HPP
#define PARKA_SYNTAX_AST_SYNTAX_HPP

#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/util/Project.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class SyntaxTree
	{
		// TODO: Project metadata
		Array<ModuleSyntax> _modules;
		Array<EntitySyntaxId> _packageIds;
		// TODO: External package ids

	private:

		SyntaxTree(Array<ModuleSyntax>&& modules, Array<EntitySyntaxId> packageIds) :
		_modules(std::move(modules)),
		_packageIds(std::move(packageIds))
		{}

	public:

		SyntaxTree(SyntaxTree&&) = default;
		SyntaxTree(const SyntaxTree&) = delete;

		static SyntaxTree parse(const Project& project);

		const auto& modules() const { return _modules; }
		const auto& packageIds() const { return _packageIds; }
	};
}

#endif
