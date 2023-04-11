#ifndef PARKA_SYNTAX_MODULE_SYNTAX_HPP
#define PARKA_SYNTAX_MODULE_SYNTAX_HPP

#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/util/Array.hpp"
#include "parka/file/File.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class ModuleSyntax
	{
		String _filepath;
		Array<EntitySyntaxId> _functionIds;
		Array<EntitySyntaxId> _structIds;

		ModuleSyntax(String&& filepath, Array<EntitySyntaxId>&& functionIds, Array<EntitySyntaxId>&& structIds) :
		_filepath(std::move(filepath)),
		_functionIds(std::move(functionIds)),
		_structIds(std::move(structIds))
		{}

	public:

		ModuleSyntax(ModuleSyntax&&) = default;
		ModuleSyntax(const ModuleSyntax&) = delete;
		~ModuleSyntax() = default;

		static Optional<ModuleSyntax> parse(const File& file);

		const auto& filename() const { return _filepath; }
		const auto& functionIds() const { return _functionIds; }
		const auto& structIds() const { return _structIds; }
	};
}

#endif