#include "parka/validator/Validator.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/enum/OperatorType.hpp"
#include "parka/ir/BinaryExpression.hpp"
#include "parka/ir/Package.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/LocalSymbolTable.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/symbol/VariableEntry.hpp"
#include "parka/util/Array.hpp"

namespace parka::validator
{
	using namespace parka::ir;

	// static bool validateFunctions(Array<FunctionIr*>& functions, Array<FunctionEntry>& entries)
	// {
	// 	bool success = true;

	// 	for (auto& entry : entries)
	// 	{
	// 		auto *ir = entry.resolve();

	// 		if (!ir)
	// 		{
	// 			success = false;
	// 			continue;
	// 		}

	// 		functions.push(ir);
	// 	}

	// 	return success;
	// }

	// static bool validatePackage(Array<FunctionIr*>& functions, PackageSymbolTable& symbolTable)
	// {
	// 	bool success = true;

	// 	if (!validateFunctions(functions, symbolTable.functions()))
	// 		success = false;

	// 	// TODO: Structs and packages
	// 	// TODO: Implement this

	// 	return success;
	// }

	Optional<Ir> validateAst(const ast::Ast& ast)
	{
		auto success = true;
		const auto& package = ast.globalPackage();
		auto symbolTable = PackageSymbolTable(package);
		auto functions = Array<FunctionIr*>();
		auto *entryPoint = (FunctionIr*)nullptr;

		for (auto& entry : symbolTable.functions())
		{
			auto *ir = entry.resolve();

			if (!ir)
			{
				success = false;
				continue;
			}

			if (ir->symbol() == "main")
				entryPoint = ir;

			functions.push(ir);
		}

		if (!success)
			return {};

		// TODO: Structs and packages

		return Ir(std::move(functions), entryPoint);
	}

	FunctionIr *validateFunction(const ast::FunctionAst& ast, SymbolTable& parentSymbolTable)
	{
		auto symbolTable = LocalSymbolTable(&parentSymbolTable);
		auto prototype = validatePrototype(ast.prototype(), symbolTable);
		auto *body = validateExpression(ast.body(), symbolTable);

		if (!prototype || !body)
			return {};

		const auto& name = ast.prototype().identifier().text();
		auto symbol = symbolTable.createSymbol(name);

		return new FunctionIr(std::move(symbol), *prototype, *body);
	}

	static Optional<Type> validateReturnType(const Optional<ast::TypeAnnotationAst>& syntax, LocalSymbolTable& symbolTable)
	{
		if (!syntax)
			return Type::voidType;

		return validateTypeAnnotation(*syntax, symbolTable);
	}

	Optional<PrototypeIr> validatePrototype(const ast::PrototypeAst& prototype, LocalSymbolTable& symbolTable)
	{
		auto success = true;
		const auto parameterCount = prototype.parameters().length();
		auto parameters = Array<ParameterIr*>(parameterCount);

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

		return PrototypeIr(std::move(parameters), *returnType);
	}

	Optional<Type> validateTypeAnnotation(const ast::TypeAnnotationAst& ast, SymbolTable& symbolTable)
	{
		auto *resolution = symbolTable.resolve(ast.identifier());

		if (!resolution)
			return {};

		auto* typeBase = dynamic_cast<TypeBase*>(resolution);
		
		if (!typeBase)
		{
			log::error(ast.snippet(), "$ is not a type name.", ast.identifier());
			return {};
		}

		return Type(*typeBase);
	}

	ParameterIr *validateParameter(const ast::ParameterAst& ast, LocalSymbolTable& symbolTable)
	{
		auto type = validateTypeAnnotation(ast.annotation(), symbolTable);

		if (!type)
			return {};

		return new ParameterIr(*type);
	}

	ExpressionIr *validateExpression(const ast::ExpressionAst& ast, LocalSymbolTable& symbolTable)
	{
		switch (ast.expressionType)
		{
			case ExpressionType::Binary:
				return validateBinaryExpression(static_cast<const ast::BinaryExpressionAst&>(ast), symbolTable);

			case ExpressionType::Block:
				return validateBlockExpression(static_cast<const ast::BlockExpressionAst&>(ast), symbolTable);

			case ExpressionType::Call:
				break;

			case ExpressionType::Conditional:
				break;

			case ExpressionType::Identifier:
				return validateIdentifierExpression(static_cast<const ast::IdentifierExpressionAst&>(ast), symbolTable);

			case ExpressionType::If:
				break;

			case ExpressionType::Subscript:
				break;

			case ExpressionType::MemberAccess:
				break;

			case ExpressionType::Prefix:
				break;

			case ExpressionType::BoolLiteral:
				return validateBoolLiteral(static_cast<const ast::BoolLiteralAst&>(ast));

			case ExpressionType::CharLiteral:
				return validateCharLiteral(static_cast<const ast::CharLiteralAst&>(ast));

			case ExpressionType::FloatLiteral:
				return validateFloatLiteral(static_cast<const ast::FloatLiteralAst&>(ast));

			case ExpressionType::IntegerLiteral:
				return validateIntegerLiteral(static_cast<const ast::IntegerLiteralAst&>(ast));

			case ExpressionType::StringLiteral:
				return validateStringLiteral(static_cast<const ast::StringLiteralAst&>(ast));

			default:
				break;
		}

		log::fatal("Unable to validate Expression with Type: $", ast.expressionType);
	}

	BlockExpressionIr *validateBlockExpression(const ast::BlockExpressionAst& ast, LocalSymbolTable& symbolTable)
	{
		auto success = true;
		auto statements = Array<StatementIr*>(ast.statements().length());

		for (const auto *statement : ast.statements())
		{
			auto *ir = validateStatement(*statement, symbolTable);

			if (!ir)
			{
				success = false;
				continue;
			}

			statements.push(ir);
		}

		// TODO: Implement return type

		if (!success)
			return {};

		return new BlockExpressionIr(std::move(statements), Type(Type::voidType));
	}

	BinaryExpressionIr *validateBinaryExpression(const ast::BinaryExpressionAst& ast, LocalSymbolTable& symbolTable)
	{
		auto *lhs = validateExpression(ast.lhs(), symbolTable);
		auto *rhs = validateExpression(ast.rhs(), symbolTable);

		if (!lhs || !rhs)
			return {};

		const auto& lhsType = lhs->type();
		const auto& rhsType = rhs->type();
		auto operatorType = toOperatorType(ast.binaryExpressionType());
		auto *op = symbolTable.resolve(operatorType, lhsType, &rhsType);

		if (!op)
			return {};

		auto result = new BinaryExpressionIr(*lhs, *rhs, *op);

		return result;
	}

	IdentifierExpressionIr *validateIdentifierExpression(const ast::IdentifierExpressionAst& ast, LocalSymbolTable& symbolTable)
	{
		auto *resolution = symbolTable.resolve(ast.identifier());

		if (!resolution)
			return {};

		auto *value = dynamic_cast<Value*>(resolution);

		if (!value)
		{
			log::error(ast.snippet(), "Unable to get value of $ `$`.", resolution->resolvableType, resolution->symbol());
			return {};
		}

		return new IdentifierExpressionIr(*value);
	}

	static Optional<u64> getIntegerValue(const Snippet& snippet)
	{
		u64 value = 0;
		const auto length = snippet.length();

		for (usize i = 0; i < length; ++i)
		{
			auto previousValue = value;

			value *= 10;
			value += snippet[i] - '0';

			auto isOverflown = value < previousValue;

			if (isOverflown)
			{
				log::error(snippet, "Integer literal is too large to fit in a 64 bit value.");
				return {};
			} 
		}
		
		return value;
	}

	static const Type& getIntegerType(u64 value)
	{
		if (value > 0xFFFFFFFF)
			return Type::u64Type;

		if (value > 0x0000FFFF)
			return Type::u32Type;

		if (value > 0x000000FF)
			return Type::u16Type;

		return Type::u8Type;
	}

	IntegerLiteralIr *validateIntegerLiteral(const ast::IntegerLiteralAst& ast)
	{
		auto value = getIntegerValue(ast.snippet());

		if (!value)
			return {};

		const auto& type = getIntegerType(*value);

		return new IntegerLiteralIr(*value, Type(type));
	}

	static f64 parseDecimal(const Snippet& snippet)
	{
		// TODO: See if it's too big to store?
		// TODO: Parse parts as large integers and create Decimal class to store result

		f64 parts[2] = { 0.0, 0.0 }; 
		usize partLens[2] = { 0, 0 };
		u32 partIndex = 0;

		for (const auto& c : snippet)
		{
			if (c == '.')
			{
				if (partIndex == 1)
					break;

				partIndex += 1;
				continue;
			}

			parts[partIndex] *= 10;
			parts[partIndex] += c - '0';
			partLens[partIndex] += 1;
		}

		auto offset = 1.0;

		for (usize i = 0; i < partLens[1]; ++i)
			offset *= 10.0;

		auto value = parts[0] + parts[1] / offset;

		return value;
	}

	FloatLiteralIr *validateFloatLiteral(const ast::FloatLiteralAst& ast)
	{
		// TODO: handle type suffixes to determine type
		auto value = parseDecimal(ast.snippet());

		return new FloatLiteralIr(value, Type(Type::f64Type));
	}

	StringLiteralIr *validateStringLiteral(const ast::StringLiteralAst& ast)
	{
		// TODO: Handle escapes
		const auto& snippet = ast.snippet();
		auto text = snippet.substr(1, snippet.length() - 2);
		auto *context = new StringLiteralIr(std::move(text));

		return context;
	}

	CharLiteralIr *validateCharLiteral(const ast::CharLiteralAst& ast)
	{
		// TODO: Allow for integer literals from long char literals;

		const auto& snippet = ast.snippet();

		if (snippet.length() != 3)
		{
			log::error(snippet, "Char literals must contain exactly 1 characters.");
			return {};
		}

		auto value = ast.snippet()[1];

		return new CharLiteralIr(value);
	}

	BoolLiteralIr *validateBoolLiteral(const ast::BoolLiteralAst& ast)
	{
		return new BoolLiteralIr(ast.value());
	}

	StatementIr *validateStatement(const ast::StatementAst& ast, LocalSymbolTable& symbolTable)
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

	StatementIr *validateDeclarationStatement(const ast::DeclarationStatementAst& ast, LocalSymbolTable& symbolTable)
	{
		// FIXME: Update all expr an stmt validation to LocalSymbolTable
		auto *value = validateExpression(ast.value(), symbolTable);
		auto *variable = validateVariable(ast.variable(), value, symbolTable);
		auto *entry = symbolTable.declare(VariableEntry(ast.variable(), variable));

		if (!variable || !value || !entry)
			return {};

		return new DeclarationStatementIr(*variable, *value);
	}

	static Optional<Type> validateVariableType(const Optional<ast::TypeAnnotationAst>& annotation, ExpressionIr *value, LocalSymbolTable& symbolTable)
	{
		if (!annotation)
		{
			if (!value)			
				return {};
			
			auto valueType = value->type();

			return valueType;
		}

		auto annotationType = validateTypeAnnotation(*annotation, symbolTable);

		if (!annotationType || !value)
			return {};

		const auto& type = value->type();

		if (type != *annotationType)
		{
			log::error("Unable to initialize variable of type $ with type $.", annotationType, type);
			return {};
		}

		return annotationType;
	}

	VariableIr *validateVariable(const ast::VariableAst& ast, ExpressionIr *value, LocalSymbolTable& symbolTable)
	{
		auto type = validateVariableType(ast.annotation(), value, symbolTable);

		if (!type)
			return {};

		return new VariableIr(String(ast.identifier().text()), *type);
	}
}
