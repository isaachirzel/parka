#include "parka/ast/Prototype.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Function.hpp"
#include "parka/ast/Parameter.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/ir/ValueType.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Print.hpp"

namespace parka::ast
{
	// static Optional<ir::ValueType> validateReturnType(Optional<TypeAnnotationAst>& syntax, SymbolTable& symbolTable)
	// {
	// 	if (!syntax)
	// 		return ir::ValueType::voidType;

	// 	return syntax->validate(symbolTable);
	// }

	// Optional<ir::PrototypeIr> PrototypeAst::validate(SymbolTable& symbolTable)
	// {
	// 	auto success = true;
	// 	const auto parameterCount = _parameters.length();
	// 	auto parameters = Array<ir::ParameterIr*>(parameterCount);

	// 	for (auto *parameterAst : _parameters)
	// 	{
	// 		auto *context = parameterAst->validate(symbolTable);

	// 		if (context == nullptr)
	// 		{
	// 			success = false;
	// 			continue;
	// 		}

	// 		parameters.push(context);
	// 	}

	// 	auto returnType = validateReturnType(_returnType, symbolTable);

	// 	if (!returnType)
	// 		success = false;

	// 	if (!success)
	// 		return {};

	// 	auto context = ir::PrototypeIr(std::move(parameters), *returnType);

	// 	return context;
	// }

	std::ostream& operator<<(std::ostream& out, const PrototypeAst& syntax)
	{
		out << "function " << syntax._identifier << '(';

		bool isFirst = true;

		for (const auto *parameter : syntax._parameters)
		{
			if (!isFirst)
				out << ", ";

			out << *parameter;

			isFirst = false;
		}

		out << ")";

		return out;
	}
}
