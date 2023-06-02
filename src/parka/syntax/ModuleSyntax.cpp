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
	ModuleSyntax ModuleSyntax::parse(const File& file)
	{
		// TODO: Fast forwarding after encountering parse error to not stop after first failure

		print("Parsing module `$`", file.path());

		auto token = Token::initial(file);
		auto functionIds = Array<EntitySyntaxId>();
		auto structIds = Array<EntitySyntaxId>();

		while (true)
		{
			auto keywordType = KeywordSyntax::getKeywordType(token);

			switch (keywordType)
			{
				case KeywordType::Function:
				{
					auto functionId = FunctionSyntax::parse(token);

					if (!functionId)
						break;

					functionIds.push(*functionId);

					continue;
				}

				case KeywordType::StructSyntax:
				{
					auto structId = StructSyntax::parse(token);

					if (!structId)
						break;

					structIds.push(*structId);

					continue;
				}

				default:
					print("Not a keyword: `$`", token);
					break;
			}

			if (token.type() != TokenType::EndOfFile)
			{
				Log::parseError(token, "type or function definition");
			}

			break;
		}

		auto mod = ModuleSyntax(String(file.path()), std::move(functionIds), std::move(structIds));

		return mod;
	}

	// bool ModuleSyntax::validate(const EntitySyntaxId& packageId)
	// {
	// 	auto success = true;
	// 	// auto& package = SyntaxRepository::getPackage(packageId);

	// 	for (auto id : _functionIds)
	// 	{
	// 		auto& function = SyntaxRepository::getFunction(id);

	// 		if (!function.validate(packageId))
	// 			success = false;
	// 	}

	// 	for (auto id : _structIds)
	// 	{
	// 		auto& strct = SyntaxRepository::getStruct(id);

	// 		if (!strct.validate(packageId))
	// 			success = false;
	// 	}

	// 	return success;
	// }
}
