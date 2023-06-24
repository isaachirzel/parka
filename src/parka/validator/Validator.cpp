#include "parka/validator/Validator.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/ir/Package.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/util/Array.hpp"

namespace parka::validator
{
	using namespace parka::ir;

	static bool validatePackage(Array<const FunctionIr*>& functions, PackageSymbolTable& package)
	{
		bool success = true;

		for (auto& function : package.functions())
		{
			auto *ir = validate(function);

			if (ir == nullptr)
			{
				success = false;
				continue;
			}

			functions.push(ir);
		}

		// TODO: Structs and packages
		// TODO: Implement this

		return success;
	}

	Optional<ir::Ir> validate(PackageSymbolTable& package)
	{
		auto functions = Array<const FunctionIr*>();
		auto success = validatePackage(functions, package);

		if (!success)
			return {};

		return Ir(std::move(functions));
	}

	ir::FunctionIr *validate(FunctionSymbolTable& symbolTable)
	{
		auto& ast = symbolTable.ast();
		auto prototype = validate(ast.prototype());
		auto *body = validate(symbolTable.body(), *this);

		if (!prototype || !body)
			return {};

		auto *context = new ir::FunctionIr(getSymbol(), *prototype, *body);

		return context;
	}

	static Optional<ir::ValueType> validateReturnType(const Optional<ast::TypeAnnotationAst>& syntax, SymbolTable& symbolTable)
	{
		if (!syntax)
			return ir::ValueType::voidType;

		return validate(*syntax, symbolTable);
	}

	Optional<ir::PrototypeIr> validate(ast::PrototypeAst& prototype, SymbolTable& symbolTable)
	{
		auto success = true;
		const auto parameterCount = prototype.parameters().length();
		auto parameters = Array<ir::ParameterIr*>(parameterCount);

		for (auto *parameterAst : prototype.parameters())
		{
			auto *context = validate(parameterAst, symbolTable);

			if (context == nullptr)
			{
				success = false;
				continue;
			}

			parameters.push(context);
		}

		auto returnType = validateReturnType(prototype.returnType(), symbolTable);

		if (!returnType)
			success = false;

		if (!success)
			return {};

		return ir::PrototypeIr(std::move(parameters), *returnType);
	}

	Optional<ir::ValueType> validate(const ast::TypeAnnotationAst&, SymbolTable&)
	{
		log::notImplemented(here());
	}

	ir::ParameterIr *validate(ast::ParameterAst& ast, SymbolTable& symbolTable)
	{
		auto isDeclared = symbolTable.declare(ast);
		auto valueType = _annotation.validate(symbolTable);

		if (!isDeclared || !valueType)
			return {};

		return new ir::ParameterIr(*valueType);
	}

	ir::ExpressionIr *validate(ast::ExpressionAst& expression, SymbolTable&)
	{
		switch (expression.expressionType)
		{
			case ExpressionType::Binary:
				break;

			case ExpressionType::Block:
				break;

			case ExpressionType::Call:
				break;

			case ExpressionType::Conditional:
				break;

			case ExpressionType::Identifier:
				break;

			case ExpressionType::If:
				break;

			case ExpressionType::Subscript:
				break;

			case ExpressionType::MemberAccess:
				break;

			case ExpressionType::Prefix:
				break;

			case ExpressionType::BoolLiteral:
				break;

			case ExpressionType::CharLiteral:
				break;

			case ExpressionType::FloatLiteral:
				break;

			case ExpressionType::IntegerLiteral:
				break;

			case ExpressionType::StringLiteral:
				break;

			default:
				break;
		}

		log::fatal("Unable to validate Expression with Type: $", expression.expressionType);
	}
}
