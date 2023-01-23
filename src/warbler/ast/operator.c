#include "warbler/ast/operator.h"

Operators operatorsCreate()
{
	Operators operators = { 0 };

	arrayInit(&operators.adds, 0);

	return operators;
}
