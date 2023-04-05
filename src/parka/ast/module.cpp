#include "parka/ast/module.hpp"
#include "parka/ast/function.hpp"
#include "parka/ast/keyword.hpp"
#include "parka/ast/package.hpp"
#include "parka/ast/struct.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/token.hpp"
#include "parka/util/array.hpp"
#include "parka/util/path.hpp"
#include "parka/util/print.hpp"

Optional<Module> Module::parse(const File& file)
{
	// TODO: Fast forwarding after encountering parse error to not stop after first failure
	print("Parsing module `$`", file.path());
	auto success = true;
	auto token = Token::initial(file);
	auto functionIds = Array<EntityId>();
	auto structIds = Array<EntityId>();

	while (true)
	{
		auto keywordType = Keyword::getKeywordType(token);

		switch (keywordType)
		{
			case KeywordType::Function:
			{
				auto functionId = Function::parse(token);

				if (!functionId)
				{
					success = false;
					break;
				}

				functionIds.push(*functionId);

				continue;
			}

			case KeywordType::Struct:
			{
				auto structId = Struct::parse(token);

				if (!structId)
				{
					success = false;
					break;
				}

				structIds.push(*structId);

				continue;
			}

			default:
				print("Not a keyword: $", token);
				break;
		}

		if (token.type() != TokenType::EndOfFile)
		{
			printParseError(token, "type or function definition");
			// success = false;
		}

		break;
	}

	if (!success)
		return {};

	auto mod = Module(String(file.path()), std::move(functionIds), std::move(structIds));

	return mod;
}

bool Module::validate(const EntityId& packageId)
{
	auto success = true;
	// auto& package = NodeBank::getPackage(packageId);

	for (auto id : _functionIds)
	{
		auto& function = NodeBank::getFunction(id);

		if (!function.validate(packageId))
			success = false;
	}

	for (auto id : _structIds)
	{
		auto& strct = NodeBank::getStruct(id);

		if (!strct.validate(packageId))
			success = false;
	}

	return success;
}
