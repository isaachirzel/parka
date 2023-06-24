#include "parka/ast/Module.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Function.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/Package.hpp"
#include "parka/ast/Struct.hpp"

#include "parka/parser/Token.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Path.hpp"
#include "parka/util/Print.hpp"

namespace parka::ast
{
	ModuleAst::ModuleAst(String&& filepath, Array<FunctionAst*>&& functions, Array<StructAst*>&& structs):
	_filepath(std::move(filepath)),
	_functions(std::move(functions)),
	_structs(std::move(structs))
	{}

	std::ostream& operator<<(std::ostream& out, const ModuleAst& mod)
	{
		auto indent = Indent(out);

		out << indent << "module `" << mod._filepath << "`\n";
		out << indent << "{\n";

		// TODO: Reimplement

		// {
		// 	auto subindent = Indent(out);

		// 	for (const auto *function : mod._functions)
		// 	{
		// 		out << subindent << *function << '\n';
		// 	}

		// 	for (const auto *strct : mod._structs)
		// 	{
		// 		out << subindent << *strct << '\n';
		// 	}
		// }

		out << indent << "}";

		return out;
	}
}
