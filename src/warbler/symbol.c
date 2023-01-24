#include "warbler/symbol.h"
#include "warbler/util/print.h"

char *createSymbol(const char *package, const Token *name)
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

const char *symbolTypeName(SymbolType type)
{
	switch (type)
	{
		case SYMBOL_PACKAGE:
			return "package";
		case SYMBOL_STRUCT:
			return "struct";
		case SYMBOL_PRIMITIVE:
			return "primitive";
		case SYMBOL_FUNCTION:
			return "function";
		case SYMBOL_VARIABLE:
			return "variable";
		case SYMBOL_PARAMETER:
			return "parameter";
		default:
			break;
	}

	exitWithErrorFmt("Unable to get name for SymbolType: %d", type);
}
