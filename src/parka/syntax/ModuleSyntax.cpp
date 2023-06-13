#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/syntax/StructSyntax.hpp"

#include "parka/Token.hpp"
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
}
