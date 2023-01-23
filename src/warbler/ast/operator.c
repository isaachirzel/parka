#include "warbler/ast/operator.h"

Operators operatorsCreate()
{
	Operators operators = { 0 };

	arrayCreate(&operators.adds, sizeof(Operator), 0);

	return operators;
}
