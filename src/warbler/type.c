#include <warbler/type.h>
#include <warbler/util/print.h>

const char *constantTypeName(LiteralType type)
{
	switch (type)
	{
		case LITERAL_CHARACTER:
			return "char literal";

		case LITERAL_STRING:
			return "string literal";
			
		case LITERAL_INTEGER:
			return "integer literal";

		case LITERAL_FLOAT:
			return "float literal";

		case LITERAL_BOOLEAN:
			return "bool literal";

		default:
            break;
	}

    exitWithErrorFmt("Unable to get name for LiteralType: %d.", type);
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
