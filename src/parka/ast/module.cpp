#include "parka/ast/module.hpp"
#include "parka/ast/function/function.hpp"
#include "parka/ast/struct.hpp"
#include "parka/entity/node_bank.hpp"
#include "parka/symbol/symbol_table.hpp"
#include "parka/symbol/symbol_table.hpp"
#include "parka/token.hpp"
#include "parka/util/array.hpp"
#include "parka/util/path.hpp"
#include "parka/util/print.hpp"

Optional<Module> Module::parse(const File& file, const String& package)
{
	printFmt("Parsing file: %s", file.path().c_str());
	// TODO: Fast forwarding after encountering parse error to not stop after first failure
	auto success = true;
	auto token = Token::initial(file);
	auto functionIds = Array<EntityId>();
	auto structIds = Array<EntityId>();

	do
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
	
	} while (false);

	if (!success)
		return {};

	auto filename = path::getFilename(file.path());
	auto mod = Module(std::move(filename), std::move(functionIds), std::move(structIds));

	return mod;
}

bool Module::validate(Table<EntityId>& globalSymbols, const String& packageSymbol)
{
	print("Validating module");

	auto success = true;
	auto symbols = SymbolTable(globalSymbols, packageSymbol);

	for (auto id : _functionIds)
	{
		auto& function = NodeBank::getFunction(id);

		if (!function.validate(symbols))
			success = false;
	}

	for (auto id : _structIds)
	{
		auto& strct = NodeBank::getStruct(id);

		if (!strct.validate(symbols))
			success = false;
	}

	return success;
}
