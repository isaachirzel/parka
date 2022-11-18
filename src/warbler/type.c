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

    exitWithErrorFmt("Invalid literal type: %d.", type);
}