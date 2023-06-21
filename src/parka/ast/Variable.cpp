#include "parka/ast/Variable.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/TypeAnnotation.hpp"

#include "parka/util/Print.hpp"

namespace parka::ast
{
	// static Optional<ir::ValueType> validateType(Optional<TypeAnnotationAst>& annotation, ir::ExpressionIr *value, SymbolTable& symbolTable)
	// {
	// 	if (!annotation)
	// 	{
	// 		if (!value)			
	// 			return {};
			
	// 		return value->valueType();
	// 	}

	// 	auto annotationType = annotation->validate(symbolTable);

	// 	if (!annotationType || !value)
	// 		return {};

	// 	auto valueType = value->valueType();

	// 	if (!valueType.canConvertTo(*annotationType))
	// 	{
	// 		log::error("Unable to initialize variable of type $ with type $.", annotationType, valueType);
	// 		return {};
	// 	}

	// 	return annotationType;
	// }

	// ir::VariableIr *VariableAst::validate(SymbolTable &symbolTable, ir::ExpressionIr *value)
	// {
	// 	auto declared = symbolTable.declare(*this);
	// 	auto type = validateType(_annotation, value, symbolTable);

	// 	if (!type || !declared)
	// 		return nullptr;

	// 	auto *context = new ir::VariableIr(String(name()), *type);

	// 	_context = context;

	// 	return context;
	// }
}
