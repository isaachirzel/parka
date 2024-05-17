#include "parka/validator/Validator.hpp"
#include "parka/ast/AssignmentStatementAst.hpp"
#include "parka/ast/CallExpressionAst.hpp"
#include "parka/ast/DeclarationStatementAst.hpp"
#include "parka/ast/ExpressionStatementAst.hpp"
#include "parka/ast/ForStatementAst.hpp"
#include "parka/ast/FunctionAst.hpp"
#include "parka/ast/IfStatementAst.hpp"
#include "parka/ast/TypeAnnotationAst.hpp"
#include "parka/enum/ExpressionType.hpp"
#include "parka/enum/ResolvableType.hpp"
#include "parka/enum/StatementType.hpp"
#include "parka/ir/AssignmentStatementIr.hpp"
#include "parka/ir/BinaryExpressionIr.hpp"
#include "parka/ir/BlockStatementIr.hpp"
#include "parka/ir/CallExpressionIr.hpp"
#include "parka/ir/DeclarationStatementIr.hpp"
#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/ExpressionStatementIr.hpp"
#include "parka/ir/ForStatementIr.hpp"
#include "parka/ir/FunctionIr.hpp"
#include "parka/ir/IdentifierExpressionIr.hpp"
#include "parka/ir/ReturnStatementIr.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/symbol/VariableEntry.hpp"
#include "parka/util/Array.hpp"

namespace parka::validator
{
	using namespace parka::ir;
	using namespace parka::ast;

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

	static bool validateEntryPoint(const ir::FunctionIr& ir, const ast::FunctionAst& ast)
	{
		bool success = true;

		if (ir.prototype().parameters().length() > 0)
		{
			const auto& parameters = ast.prototype().parameters();
			auto& first = *parameters.front();
			auto& last = *parameters.back();
			auto snippet = first.snippet() + last.snippet();

			log::error(snippet, "Entry point `main` may not have any parameters.");
			success = false;
		}

		if (ir.prototype().returnType() != Type::i32Type && ir.prototype().returnType() != Type::voidType)
		{
			log::error(ast.prototype().returnType()->snippet(), "Entry point `main` must return either $ or $.", Type::i32Type, Type::voidType);
			success = false;
		}

		return success;
	}

	Result<Ir> validateAst(const Ast& ast)
	{
		const auto& package = ast.globalPackage();
		auto symbolTable = PackageSymbolTable(package);
		auto functions = Array<FunctionIr*>();
		auto *entryPoint = (FunctionIr*)nullptr;

		for (auto& entry : symbolTable.functions())
		{
			auto *ir = entry.resolve();

			if (!ir)
				continue;

			if (!entryPoint && ir->symbol() == "main")
			{
				entryPoint = ir;

				validateEntryPoint(*ir, entry.ast());
			}
			
			functions.push(ir);
		}

		// TODO: Structs and packages

		return Ir(ast.name(), std::move(functions), entryPoint);
	}

	FunctionIr *validateFunction(const FunctionAst& ast, SymbolTable& parentSymbolTable)
	{
		auto symbolTable = FunctionSymbolTable(&parentSymbolTable);
		auto prototype = validatePrototype(ast.prototype(), symbolTable);

		if (!prototype)
			return {};

		const auto& name = ast.prototype().identifier().text();
		auto symbol = symbolTable.createSymbol(name);

		if (!ast.hasBody())
			return new FunctionIr(std::move(symbol), *prototype, nullptr);

		auto* body = validateBlockStatement(ast.body(), symbolTable);

		if (!body)
			return {};

		return new FunctionIr(std::move(symbol), *prototype, body);
	}

	static Result<Type> validateReturnType(const Result<TypeAnnotationAst>& syntax, FunctionSymbolTable& symbolTable)
	{
		if (!syntax)
			return Type::voidType;

		return validateTypeAnnotation(*syntax, symbolTable);
	}

	Result<PrototypeIr> validatePrototype(const PrototypeAst& prototype, FunctionSymbolTable& symbolTable)
	{
		const auto parameterCount = prototype.parameters().length();
		auto parameters = Array<ParameterIr*>(parameterCount);

		for (auto* parameterAst : prototype.parameters())
		{
			auto* parameter = validateParameter(*parameterAst, symbolTable);
			auto* entry = symbolTable.declare(ParameterEntry(*parameterAst, parameter));

			if (!parameter || !entry)
				continue;

			parameters.push(parameter);
		}

		auto returnType = validateReturnType(prototype.returnType(), symbolTable);

		if (!returnType || parameters.length() != prototype.parameters().length())
			return {};

		symbolTable.setReturnType(*returnType);

		return PrototypeIr(std::move(parameters), *returnType);
	}

	Result<Type> validateTypeAnnotation(const TypeAnnotationAst& ast, SymbolTable& symbolTable)
	{
		auto *resolution = symbolTable.resolveSymbol(ast.identifier());

		if (!resolution)
		{
			log::error(ast.identifier().snippet(), "The type `$` could not be found in this scope.", ast.identifier());
			return {};
		}

		auto* typeBase = dynamic_cast<TypeBase*>(resolution);
		
		if (!typeBase)
		{
			// TODO: Figure out what the referred thing was for better clarity
			// TODO: Maybe show "other thing defined here"
			log::error(ast.snippet(), "Expected a type, but `$` was found.", ast.identifier());
			return {};
		}

		return Type(*typeBase);
	}

	ParameterIr *validateParameter(const ParameterAst& ast, FunctionSymbolTable& symbolTable)
	{
		auto type = validateTypeAnnotation(ast.annotation(), symbolTable);

		if (!type)
			return {};

		return new ParameterIr(*type);
	}

	ExpressionIr *validateExpression(const ExpressionAst& ast, FunctionSymbolTable& symbolTable)
	{
		switch (ast.expressionType)
		{
			case ExpressionType::Binary:
				return validateBinaryExpression(static_cast<const BinaryExpressionAst&>(ast), symbolTable);

			case ExpressionType::Call:
				return validateCallExpression(static_cast<const CallExpressionAst&>(ast), symbolTable);

			case ExpressionType::Conditional:
				break;

			case ExpressionType::Identifier:
				return validateIdentifierExpression(static_cast<const IdentifierExpressionAst&>(ast), symbolTable);

			case ExpressionType::If:
				break;

			case ExpressionType::Subscript:
				break;

			case ExpressionType::MemberAccess:
				break;

			case ExpressionType::Prefix:
				break;

			case ExpressionType::BoolLiteral:
				return validateBoolLiteral(static_cast<const BoolLiteralAst&>(ast));

			case ExpressionType::CharLiteral:
				return validateCharLiteral(static_cast<const CharLiteralAst&>(ast));

			case ExpressionType::FloatLiteral:
				return validateFloatLiteral(static_cast<const FloatLiteralAst&>(ast));

			case ExpressionType::IntegerLiteral:
				return validateIntegerLiteral(static_cast<const IntegerLiteralAst&>(ast));

			case ExpressionType::StringLiteral:
				return validateStringLiteral(static_cast<const StringLiteralAst&>(ast));

			default:
				break;
		}

		log::fatal("Unable to validate Expression with Type: $", ast.expressionType);
	}

	BinaryExpressionIr *validateBinaryExpression(const BinaryExpressionAst& ast, FunctionSymbolTable& symbolTable)
	{
		auto *lhs = validateExpression(ast.lhs(), symbolTable);
		auto *rhs = validateExpression(ast.rhs(), symbolTable);

		if (!lhs || !rhs)
			return {};

		const auto& lhsType = lhs->type();
		const auto& rhsType = rhs->type();
		auto *op = symbolTable.resolveBinaryOperator(ast.binaryExpressionType(), lhsType, rhsType);

		if (!op)
			return {};

		auto result = new BinaryExpressionIr(*lhs, *rhs, *op);

		return result;
	}

	CallExpressionIr* validateCallExpression(const CallExpressionAst& ast, FunctionSymbolTable& symbolTable)
	{
		auto* subject = validateExpression(ast.subject(), symbolTable);

		if (!subject)
			return {};

		// TODO: Implement call expression operators

		if (subject->expressionType != ExpressionType::Identifier)
		{
			log::error(ast.subject().snippet(), "Unable to call expression as function.");
			return {};
		}

		auto& reference = static_cast<IdentifierExpressionIr&>(*subject);
		auto& lvalue = reference.value();

		if (lvalue.resolvableType != ResolvableType::Function)
		{
			log::error(ast.subject().snippet(), "Unable to call $ as function.", lvalue.resolvableType);
			return {};
		}

		auto& function = static_cast<const FunctionIr&>(lvalue);
		auto& prototype = function.prototype();

		if (prototype.parameters().length() != ast.arguments().length())
		{
			log::error(ast.snippet(), "This function takes $ argument(s) but $ were given.", prototype.parameters().length(), ast.arguments().length());
			return {};
		}

		auto arguments = Array<ArgumentIr>(ast.arguments().length());

		for (usize i = 0; i < ast.arguments().length(); ++i)
		{
			auto& valueAst = *ast.arguments()[i];
			auto& parameter = *prototype.parameters()[i];
			auto* value = validateExpression(valueAst, symbolTable);

			if (!value)
				continue;

			auto conversion = symbolTable.resolveConversion(parameter.type(), value->type());

			if (!conversion)
			{
				log::error(valueAst.snippet(), "Parameter $ calls for $ but $ was passed in.", parameter.symbol(), parameter.type(), value->type());
				continue;
			}

			arguments.push(ArgumentIr(*value, *conversion));
		}
		
		if (arguments.length() != ast.arguments().length())
			return {};

		return new CallExpressionIr(function, std::move(arguments));
	}

	IdentifierExpressionIr *validateIdentifierExpression(const IdentifierExpressionAst& ast, FunctionSymbolTable& symbolTable)
	{
		auto *result = symbolTable.resolveSymbol(ast.identifier());

		if (!result)
		{
			log::error(ast.snippet(), "A definition for the name `$` could not be found in this scope.", ast.identifier());
			return {};
		}

		auto *value = dynamic_cast<LValueIr*>(result);

		if (!value)
		{
			log::error(ast.snippet(), "Unable to get value of $ `$`.", result->resolvableType, result->symbol());
			return {};
		}

		return new IdentifierExpressionIr(*value);
	}

	static Result<u64> getIntegerValue(const Snippet& snippet)
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

	IntegerLiteralIr *validateIntegerLiteral(const IntegerLiteralAst& ast)
	{
		auto value = getIntegerValue(ast.snippet());

		if (!value)
			return {};

		return new IntegerLiteralIr(*value);
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

	FloatLiteralIr *validateFloatLiteral(const FloatLiteralAst& ast)
	{
		// TODO: handle type suffixes to determine f64 vs f32
		auto value = parseDecimal(ast.snippet());

		return new FloatLiteralIr(value);
	}

	StringLiteralIr *validateStringLiteral(const StringLiteralAst& ast)
	{
		// TODO: Handle escapes
		const auto& snippet = ast.snippet();
		auto text = snippet.substr(1, snippet.length() - 2);
		auto *context = new StringLiteralIr(std::move(text));

		return context;
	}

	CharLiteralIr *validateCharLiteral(const CharLiteralAst& ast)
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

	BoolLiteralIr *validateBoolLiteral(const BoolLiteralAst& ast)
	{
		return new BoolLiteralIr(ast.value());
	}

	StatementIr *validateStatement(const StatementAst& ast, FunctionSymbolTable& symbolTable)
	{
		switch (ast.statementType)
		{
			case StatementType::Declaration:
				return validateDeclarationStatement(static_cast<const DeclarationStatementAst&>(ast), symbolTable);

			case StatementType::Expression:
				return validateExpressionStatement(static_cast<const ExpressionStatementAst&>(ast), symbolTable);

			case StatementType::Return:
				return validateReturnStatement(static_cast<const ReturnStatementAst&>(ast), symbolTable);

			case StatementType::Break:
				return validateBreakStatement(static_cast<const BreakStatementAst&>(ast), symbolTable);

			case StatementType::Continue:
				return validateContinueStatement(static_cast<const ContinueStatementAst&>(ast), symbolTable);

			case StatementType::Yield:
				return validateYieldStatement(static_cast<const YieldStatementAst&>(ast), symbolTable);

			case StatementType::For:
				return validateForStatement(static_cast<const ForStatementAst&>(ast), symbolTable);

			case StatementType::Block:
				return validateBlockStatement(static_cast<const BlockStatementAst&>(ast), symbolTable);

			case StatementType::Assignment:
				return validateAssignmentStatement(static_cast<const AssignmentStatementAst&>(ast), symbolTable);

			case StatementType::If:
				return validateIfStatement(static_cast<const ast::IfStatementAst&>(ast), symbolTable);

			default:
				break;
		}

		log::fatal("Unable to validate Statement with Type: $", ast.statementType);
	}

	DeclarationStatementIr *validateDeclarationStatement(const DeclarationStatementAst& ast, FunctionSymbolTable& symbolTable)
	{
		// FIXME: Update all expr an stmt validation to FunctionSymbolTable
		auto* value = validateExpression(ast.value(), symbolTable);
		auto* variable = validateVariable(ast.variable(), value, symbolTable);
		auto* entry = symbolTable.declare(VariableEntry(ast.variable(), variable));

		if (!variable || !value)
			return {};

		auto conversion = symbolTable.resolveConversion(variable->type(), value->type());

		if (!conversion || !entry)
			return {};

		return new DeclarationStatementIr(*variable, *value, *conversion);
	}

	ExpressionStatementIr* validateExpressionStatement(const ExpressionStatementAst& ast, FunctionSymbolTable& symbolTable)
	{
		auto* expression = validateExpression(ast.expression(), symbolTable);

		if (!expression)
			return {};

		return new ExpressionStatementIr(*expression);
	}

	AssignmentStatementIr *validateAssignmentStatement(const AssignmentStatementAst& ast, FunctionSymbolTable& symbolTable)
	{
		auto* lhs = validateExpression(ast.identifier(), symbolTable);
		auto* value = validateExpression(ast.value(), symbolTable);

		if (!lhs || !value)
			return {};
		
		if (lhs->expressionType != ExpressionType::Identifier)
		{
			log::error(ast.identifier().snippet(), "Expected LValue. This expression is not a modifiable value.");
			return {};
		}

		auto& identifier = static_cast<IdentifierExpressionIr&>(*lhs);
		auto conversion = symbolTable.resolveConversion(identifier.type(), value->type());

		if (!conversion)
		{
			log::error("Unable to assign $ to $.", value->type(), identifier.type());
			return {};
		}

		return new AssignmentStatementIr(identifier, *value, *conversion, ast.assignmentType());
	}

	ReturnStatementIr *validateReturnStatement(const ReturnStatementAst& ast, FunctionSymbolTable& symbolTable)
	{
		if (!ast.hasValue())
		{
			if (symbolTable.returnType() == Type::voidType)
				return new ReturnStatementIr();

			log::error(ast.snippet(), "Expected $ return value but none was given.", symbolTable.returnType());
			return {};
		}

		auto* value = validateExpression(ast.value(), symbolTable);

		if (!value)
			return {};

		auto conversion = symbolTable.resolveConversion(symbolTable.returnType(), value->type());

		if (!conversion)
		{
			// TODO: Highlight function return type
			log::error(ast.value().snippet(), "Unable to return $ in function expecting $.", value->type(), symbolTable.returnType());
			return {};
		}
		
		return new ReturnStatementIr(*value, *conversion);
	}

	BreakStatementIr *validateBreakStatement(const BreakStatementAst& ast, FunctionSymbolTable& symbolTable)
	{
		// Must be in a loop
		log::notImplemented(here());
	}

	ContinueStatementIr *validateContinueStatement(const ContinueStatementAst& ast, FunctionSymbolTable& symbolTable)
	{
		// Must be in a loop
		log::notImplemented(here());
	}

	YieldStatementIr *validateYieldStatement(const YieldStatementAst& ast, FunctionSymbolTable& symbolTable)
	{
		// Must be in an block/if statement
		log::notImplemented(here());
	}

	ForStatementIr *validateForStatement(const ForStatementAst& ast, FunctionSymbolTable& symbolTable)
	{
		auto* declaration = validateDeclarationStatement(ast.declaration(), symbolTable);

		if (!declaration)
			return {};

		auto* condition = validateExpression(ast.condition(), symbolTable);
		auto* action = validateStatement(ast.action(), symbolTable);
		auto* body = validateBlockStatement(ast.body(), symbolTable);

		if (!condition  || !action || !body)
			return {};

		auto conversion = symbolTable.resolveConversion(Type::boolType, condition->type());

		if (!conversion)
		{
			log::error("Expression could not be converted from `$` to `$`.", condition->type(), Type::boolType);
			return {};
		}

		return new ForStatementIr(*declaration, *condition, *conversion, *action, *body);
	}

	BlockStatementIr *validateBlockStatement(const BlockStatementAst& ast, FunctionSymbolTable& symbolTable)
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

		if (!success)
			return {};

		return new BlockStatementIr(std::move(statements));
	}
	
	IfStatementIr* validateIfStatement(const IfStatementAst& ast, FunctionSymbolTable& symbolTable)
	{
		auto* condition = validateExpression(ast.condition(), symbolTable);
		auto* thenCase = validateStatement(ast.thenCase(), symbolTable);
		auto* elseCase = ast.hasElseCase()
			? validateStatement(ast.elseCase(), symbolTable)
			: nullptr;

		if (!condition || !thenCase || (ast.hasElseCase() && !elseCase))
			return {};

		auto conversion = symbolTable.resolveConversion(Type::boolType, condition->type());

		if (!conversion)
		{
			log::error(ast.condition().snippet(), "Unable to use expression of type $ as if condition.", condition->type());
			return {};
		}

		return new IfStatementIr(*condition, *conversion, *thenCase, elseCase);
	}

	static Result<Type> validateVariableType(const Result<TypeAnnotationAst>& annotation, ExpressionIr *value, FunctionSymbolTable& symbolTable)
	{
		if (!annotation)
		{
			if (!value)
				return {};
			
			auto valueType = value->type();

			return valueType;
		}

		auto annotationTypeResult = validateTypeAnnotation(*annotation, symbolTable);

		if (!annotationTypeResult || !value)
			return {};

		auto annotationType = *annotationTypeResult;
		auto conversion = symbolTable.resolveConversion(annotationType, value->type());

		if (!conversion)
		{
			log::error("Unable to initialize variable of type $ with a value of type $.", annotationType, value->type());
			return {};
		}

		return annotationType;
	}

	VariableIr *validateVariable(const VariableAst& ast, ExpressionIr *value, FunctionSymbolTable& symbolTable)
	{
		auto type = validateVariableType(ast.annotation(), value, symbolTable);

		if (!type)
			return {};

		return new VariableIr(String(ast.identifier().text()), *type);
	}
}
