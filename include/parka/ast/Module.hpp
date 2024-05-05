#ifndef PARKA_AST_MODULE_HPP
#define PARKA_AST_MODULE_HPP

#include "parka/ast/Function.hpp"
#include "parka/ast/Struct.hpp"
#include "parka/util/Array.hpp"

namespace parka::ast
{
	class ModuleAst
	{
		String _filepath;
		Array<FunctionAst*> _functions;
		Array<StructAst*> _structs;

	public:

		ModuleAst(String&& filepath, Array<FunctionAst*>&& functions, Array<StructAst*>&& structs):
		_filepath(std::move(filepath)),
		_functions(std::move(functions)),
		_structs(std::move(structs))
		{}
		ModuleAst(ModuleAst&&) = default;
		ModuleAst(const ModuleAst&) = delete;

		const auto& filename() const { return _filepath; }
		const auto& functions() const { return _functions; }
		const auto& structs() const { return _structs; }
	};
}

#endif