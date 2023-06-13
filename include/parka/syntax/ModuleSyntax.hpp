#ifndef PARKA_SYNTAX_MODULE_SYNTAX_HPP
#define PARKA_SYNTAX_MODULE_SYNTAX_HPP

#include "parka/syntax/EntitySyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/syntax/StructSyntax.hpp"
#include "parka/util/Array.hpp"
#include "parka/file/File.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Table.hpp"

#include <ostream>

namespace parka
{
	class ModuleSyntax
	{
		String _filepath;
		Array<FunctionSyntax*> _functions;
		Array<StructSyntax*> _structs;

	public:

		ModuleSyntax(String&& filepath, Array<FunctionSyntax*>&& functions, Array<StructSyntax*>&& structs);
		ModuleSyntax(ModuleSyntax&&) = default;
		ModuleSyntax(const ModuleSyntax&) = delete;

		static ModuleSyntax parse(const File& file);

		const auto& filename() const { return _filepath; }
		const auto& functions() const { return _functions; }
		const auto& structs() const { return _structs; }

		friend std::ostream& operator<<(std::ostream& out, const ModuleSyntax& mod);
	};
}

#endif