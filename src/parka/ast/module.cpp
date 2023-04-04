#include "parka/ast/module.hpp"
#include "parka/ast/function/function.hpp"
#include "parka/ast/keyword.hpp"
#include "parka/ast/package.hpp"
#include "parka/ast/struct/struct.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/token.hpp"
#include "parka/util/array.hpp"
#include "parka/util/path.hpp"
#include "parka/util/print.hpp"

Optional<Module> Module::parse(const File& file)
{
	// TODO: Fast forwarding after encountering parse error to not stop after first failure
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

				functionIds.push(functionId.unwrap());

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

				structIds.push(structId.unwrap());

				continue;
			}

			default:
				break;
		}

		if (token.type() != TokenType::EndOfFile)
		{
			printParseError(token, "type or function definition");
			success = false;
		}

		break;
	}

	if (!success)
		return {};

	auto filename = path::getFilename(file.path());
	auto mod = Module(std::move(filename), std::move(functionIds), std::move(structIds));

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
