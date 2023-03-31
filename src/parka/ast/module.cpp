#include "parka/ast/module.hpp"
#include "parka/ast/function/function.hpp"
#include "parka/ast/struct/struct.hpp"
#include "parka/symbol/global_symbol_table.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/symbol/local_symbol_table.hpp"
#include "parka/symbol/local_symbol_table.hpp"
#include "parka/token.hpp"
#include "parka/util/array.hpp"
#include "parka/util/path.hpp"
#include "parka/util/print.hpp"

Optional<Module> Module::parse(const File& file, const String& package)
{
	// TODO: Fast forwarding after encountering parse error to not stop after first failure
	auto success = true;
	auto token = Token::initial(file);
	auto functionIds = Array<EntityId>();
	auto structIds = Array<EntityId>();

	while (true)
	{
		switch (token.type())
		{
			case TokenType::KeywordFunction:
			{
				auto functionId = Function::parse(token, package);

				if (!functionId)
				{
					success = false;
					break;
				}

				functionIds.push(functionId.unwrap());

				continue;
			}

			case TokenType::KeywordStruct:
			{
				auto structId = Struct::parse(token, package);

				if (!structId)
				{
					success = false;
					break;
				}

				structIds.push(structId.unwrap());

				continue;
			}

			case TokenType::EndOfFile:
				break;

			default:
				printParseError(token, "type or function definition");
				success = false;
				break;
		}

		break;
	}

	if (!success)
		return {};

	auto filename = path::getFilename(file.path());
	auto mod = Module(std::move(filename), std::move(functionIds), std::move(structIds));

	return mod;
}

bool Module::declare(GlobalSymbolTable& globalSymbols)
{
	auto success = true;

	for (auto structId : _structIds)
	{
		if (!globalSymbols.declare(structId))
			success = false;
	}

	for (auto functionId : _functionIds)
	{
		if (!globalSymbols.declare(functionId))
			success = false;
	}

	return success;
}

bool Module::validate(GlobalSymbolTable& globalSymbols, const String& packageSymbol)
{
	auto success = true;
	auto localSymbols = LocalSymbolTable(globalSymbols, packageSymbol);

	for (auto id : _functionIds)
	{
		auto& function = NodeBank::getFunction(id);

		if (!function.validate(localSymbols))
			success = false;

		localSymbols.clear();
	}

	for (auto id : _structIds)
	{
		auto& strct = NodeBank::getStruct(id);

		if (!strct.validate(localSymbols))
			success = false;
	}

	return success;
}