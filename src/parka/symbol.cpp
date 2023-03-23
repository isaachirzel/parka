#include "parka/symbol.hpp"
#include "parka/util/print.hpp"

char *createSymbolKey(const char *package, const Token& name)
{
	const char *iter = tokenGetIterator(name);
	StringBuilder builder = sbCreate(128);
	
	if (*package)
	{
		sbPushString(&builder, package);
		sbPushString(&builder, "::");
	}

	sbPushStringN(&builder, iter, name->length);

	return builder.data;
}

const char *symbolTypeName(EntityType type)
{
	switch (type)
	{
		case EntityType::Package:
			return "package";
		case EntityType::Struct:
			return "struct";
		case EntityType::Primitive:
			return "primitive";
		case EntityType::Function:
			return "function";
		case EntityType::Variable:
			return "variable";
		case EntityType::Parameter:
			return "parameter";
		default:
			break;
	}

	exitWithErrorFmt("Unable to get name for EntityType: %d", type);
}

String entityTypeGetName(EntityType type)
{
	switch (type)
	{
		case EntityType::Package:
			return "package";

		case EntityType::Struct:
			return "struct";

		case EntityType::Primitive:
			return "primitive";

		case EntityType::Function:
			return "function";

		case EntityType::Variable:
			return "variable";

		case EntityType::Parameter:
			return "parameter";

		default:
			break;
	}

	exitWithErrorFmt("Unable to get name for EntityType: %d", type);
}
