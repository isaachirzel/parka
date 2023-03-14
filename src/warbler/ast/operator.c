#include "warbler/ast/operator.h"
#include "warbler/util/print.h"

Operators operatorsCreate(void)
{
	Operators operators = { 0 };

	arrayInit(&operators.addOperators, 0);

	return operators;
}

static OperatorList *getOperatorList(Operators *operators, OperatorType type)
{
	switch (type)
	{
		case OPERATOR_ADD:
			return &operators->addOperators;

		default:
			exitWithErrorFmt("Unable to get OperatorList for Operator with type: %d", type);
	}
}

usize operatorsAddBuiltIn(Operators *operators, OperatorType type, Type *rightType, Type *returnType)
{
	OperatorList *operatorList = getOperatorList(operators, type);
	Operator operator =
	{
		.type = type,
		.rightType = *rightType,
		.returnType = *returnType,
		.isBuiltIn = true
	};
	usize index = arrayPush(operatorList, &operator);

	return index;
}
