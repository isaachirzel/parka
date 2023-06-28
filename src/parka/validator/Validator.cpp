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

	static bool validatePackage(Array<FunctionIr*>& functions, PackageSymbolTable& package)
	{
		bool success = true;

		for (auto& function : package.functions())
		{
			auto *ir = validateFunction(function);

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

	Optional<ir::Ir> validateAst(const ast::Ast& ast)
	{
		auto symbolTable = PackageSymbolTable(ast.globalPackage());

		return validatePackage(symbolTable);
	}

	Optional<ir::Ir> validatePackage(PackageSymbolTable& package)
	{
		auto functions = Array<FunctionIr*>();
		auto success = validatePackage(functions, package);

		if (!success)
			return {};

		return Ir(std::move(functions));
	}

	ir::FunctionIr *validateFunction(FunctionSymbolTable& symbolTable)
	{
		auto& ast = symbolTable.ast();
		auto prototype = validatePrototype(ast.prototype(), symbolTable);
		auto *body = validateExpression(ast.body(), symbolTable);

		if (!prototype || !body)
			return {};

		auto *context = new ir::FunctionIr(String(symbolTable.symbol()), *prototype, *body);

		return context;
	}

	static Optional<ir::ValueType> validateReturnType(const Optional<ast::TypeAnnotationAst>& syntax, SymbolTable& symbolTable)
	{
		if (!syntax)
			return ir::ValueType::voidType;

		return validateTypeAnnotation(*syntax, symbolTable);
	}

	Optional<ir::PrototypeIr> validatePrototype(const ast::PrototypeAst& prototype, SymbolTable& symbolTable)
	{
		auto success = true;
		const auto parameterCount = prototype.parameters().length();
		auto parameters = Array<ir::ParameterIr*>(parameterCount);

		for (auto *parameterAst : prototype.parameters())
		{
			auto *context = validateParameter(*parameterAst, symbolTable);

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

	Optional<ir::ValueType> validateTypeAnnotation(const ast::TypeAnnotationAst&, SymbolTable&)
	{
		log::notImplemented(here());
	}

	ir::ParameterIr *validateParameter(const ast::ParameterAst& ast, SymbolTable& symbolTable)
	{
		auto isDeclared = symbolTable.declare(ast);
		auto valueType = validateTypeAnnotation(ast.annotation(), symbolTable);

		if (!isDeclared || !valueType)
			return {};

		return new ir::ParameterIr(*valueType);
	}

	ir::ExpressionIr *validateExpression(const ast::ExpressionAst& expression, SymbolTable& symbolTable)
	{
		switch (expression.expressionType)
		{
			case ExpressionType::Binary:
				break;

			case ExpressionType::Block:
				return validateBlockExpression((const ast::BlockExpressionAst&)expression, symbolTable);

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

	ir::BlockExpressionIr *validateBlockExpression(const ast::BlockExpressionAst& ast, SymbolTable& symbolTable)
	{
		auto success = true;
		auto statements = Array<StatementIr*>(ast.statements().length());

		for (const auto *statement : ast.statements())
		{
			auto *ir = validateStatement(*statement, symbolTable);

			if (ir == nullptr)
			{
				success = false;
				continue;
			}

			statements.push(ir);
		}

		// TODO: Implement return type

		if (!success)
			return {};

		return new BlockExpressionIr(std::move(statements), ValueType(ValueType::voidType));
	}

	ir::BinaryExpressionIr *validateBinaryExpression(const ast::BinaryExpressionAst& ast, SymbolTable& symbolTable)
	{
		auto *lhs = validateExpression(ast.lhs(), symbolTable);
		auto *rhs = validateExpression(ast.rhs(), symbolTable);

		// TODO: Operators

		if (!lhs || !rhs)
			return nullptr;

		const auto& lhsType = lhs->valueType();
		const auto& rhsType = rhs->valueType();

		if (!rhsType.canConvertTo(lhsType))
		{
			log::error(ast.snippet(), "$ cannot be added to $.", rhsType, lhsType);
			return nullptr;
		}

		return new ir::BinaryExpressionIr(*lhs, *rhs, ast.binaryExpressionType(), ir::ValueType(lhsType));
	}

	ir::StatementIr *validateStatement(const ast::StatementAst& ast, SymbolTable& symbolTable)
	{
		switch (ast.statementType)
		{
			case StatementType::Declaration:
				return validateDeclarationStatement((const ast::DeclarationStatementAst&)ast, symbolTable);

			// case StatementType::Expression:
			// 	break;

			// case StatementType::Jump:
			// 	break;

			default:
				break;
		}

		log::fatal("Unable to validate Statement with Type: $", ast.statementType);
	}

	ir::StatementIr *validateDeclarationStatement(const ast::DeclarationStatementAst& ast, SymbolTable& symbolTable)
	{
		auto *value = validateExpression(ast.value(), symbolTable);
		auto *variable = validateVariable(ast.variable(), value, symbolTable);

		if (!variable || !value)
			return {};

		return new ir::DeclarationStatementIr(*variable, *value);
	}

	static Optional<ir::ValueType> validateVariableType(const Optional<ast::TypeAnnotationAst>& annotation, ir::ExpressionIr *value, SymbolTable& symbolTable)
	{
		if (!annotation)
		{
			if (!value)			
				return {};
			
			return value->valueType();
		}

		auto annotationType = validateTypeAnnotation(*annotation, symbolTable);

		if (!annotationType || !value)
			return {};

		auto valueType = value->valueType();

		if (!valueType.canConvertTo(*annotationType))
		{
			log::error("Unable to initialize variable of type $ with type $.", annotationType, valueType);
			return {};
		}

		return annotationType;
	}

	ir::VariableIr *validateVariable(const ast::VariableAst& ast, ir::ExpressionIr *value, SymbolTable& symbolTable)
	{
		auto declared = symbolTable.declare(ast);
		auto type = validateVariableType(ast.annotation(), value, symbolTable);

		if (!type || !declared)
			return nullptr;

		return new ir::VariableIr(String(ast.name()), *type);
	}
}
