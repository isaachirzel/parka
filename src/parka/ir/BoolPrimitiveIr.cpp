namespace parka::ir
{
	// BinaryOperatorIr* PrimitiveIr::getBinaryOperator(BinaryExpressionType binaryExpressionType, const TypeIr& rhs) const
	// {
	// 	if (&rhs != &instance)
	// 		return nullptr;

	// 	switch (binaryExpressionType)
	// 	{
	// 		case BinaryExpressionType::Equals:
	// 			return &binop<BinaryExpressionType::Equals, bool>();

	// 		case BinaryExpressionType::NotEquals:
	// 			return &binop<BinaryExpressionType::NotEquals, bool>();

	// 		case BinaryExpressionType::BooleanOr:
	// 			return &binop<BinaryExpressionType::BooleanOr, bool>();

	// 		case BinaryExpressionType::BooleanAnd:
	// 			return &binop<BinaryExpressionType::BooleanAnd, bool>();

	// 		default:
	// 			break;
	// 	}

	// 	return nullptr;
	// }

	// AssignmentOperatorIr* PrimitiveIr::getAssignmentOperator(AssignmentType assignmentType, const TypeIr& other) const
	// {
	// 	if (other == *this && assignmentType == AssignmentType::Assign)
	// 		return &assgn<AssignmentType::Assign, bool>();

	// 	return nullptr;
	// }
}
