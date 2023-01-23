#include "warbler/symbol.h"
#include "warbler/util/print.h"

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
