#ifndef PARKA_AST_MODULE_HPP
#define PARKA_AST_MODULE_HPP

#include "parka/ast/Entity.hpp"
#include "parka/ast/Function.hpp"
#include "parka/ast/Struct.hpp"
#include "parka/util/Array.hpp"
#include "parka/file/File.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Table.hpp"

#include <ostream>

namespace parka::ast
{
	class ModuleAst
	{
		String _filepath;
		Array<FunctionAst*> _functions;
		Array<StructAst*> _structs;

	public:

		ModuleAst(String&& filepath, Array<FunctionAst*>&& functions, Array<StructAst*>&& structs);
		ModuleAst(ModuleAst&&) = default;
		ModuleAst(const ModuleAst&) = delete;

		static ModuleAst parse(const File& file);

		const auto& filename() const { return _filepath; }
		const auto& functions() const { return _functions; }
		const auto& structs() const { return _structs; }

		friend std::ostream& operator<<(std::ostream& out, const ModuleAst& mod);
	};
}

#endif