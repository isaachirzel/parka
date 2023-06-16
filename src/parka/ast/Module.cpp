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

namespace parka
{
	ModuleSyntax::ModuleSyntax(String&& filepath, Array<FunctionSyntax*>&& functions, Array<StructSyntax*>&& structs) :
	_filepath(std::move(filepath)),
	_functions(std::move(functions)),
	_structs(std::move(structs))
	{}

	ModuleSyntax ModuleSyntax::parse(const File& file)
	{
		// TODO: Fast forwarding after encountering parse error to not stop after first failure
		auto token = Token::initial(file);
		auto functions = Array<FunctionSyntax*>();
		auto structs = Array<StructSyntax*>();

		while (true)
		{
			auto keywordType = KeywordSyntax::getKeywordType(token);

			switch (keywordType)
			{
				case KeywordType::Function:
				{
					auto *function = FunctionSyntax::parse(token);

					if (!function)
						break;

					functions.push(function);

					continue;
				}

				case KeywordType::StructSyntax:
				{
					auto *strct = StructSyntax::parse(token);

					if (!strct)
						break;

					structs.push(strct);

					continue;
				}

				default:
					break;
			}

			if (token.type() != TokenType::EndOfFile)
			{
				log::parseError(token, "type or function definition");
			}

			break;
		}

		auto mod = ModuleSyntax(String(file.path()), std::move(functions), std::move(structs));

		return mod;
	}

	std::ostream& operator<<(std::ostream& out, const ModuleSyntax& mod)
	{
		auto indent = Indent(out);

		out << indent << "module `" << mod._filepath << "`\n";
		out << indent << "{\n";

		{
			auto subindent = Indent(out);

			for (const auto *function : mod._functions)
			{
				out << subindent << *function << '\n';
			}

			for (const auto *strct : mod._structs)
			{
				out << subindent << *strct << '\n';
			}
		}

		out << indent << "}";

		return out;
	}
}
