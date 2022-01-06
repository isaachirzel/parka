#ifndef WARBLER_AST_$_STATEMENT_H
#define WARBLER_AST_$_STATEMENT_H

// local headers
#include <warbler/token.h>
#include <warbler/error.h>

typedef struct $Statement
{
} $Statement;

Error $_statement_parse($Statement *$, TokenIterator *iter);
void $_statement_free($Statement *$);

#endif
