#include "parka/validator/Validator.hpp"
#include "parka/ast/AssignmentStatementAst.hpp"
#include "parka/ast/CallExpressionAst.hpp"
#include "parka/ast/ContinueStatementAst.hpp"
#include "parka/ast/DeclarationStatementAst.hpp"
#include "parka/ast/ExpressionStatementAst.hpp"
#include "parka/ast/ForStatementAst.hpp"
#include "parka/ast/FunctionAst.hpp"
#include "parka/ast/FunctionBodyAst.hpp"
#include "parka/ast/IfStatementAst.hpp"
#include "parka/ast/TypeAnnotationAst.hpp"
#include "parka/enum/ExpressionType.hpp"
#include "parka/enum/ResolvableType.hpp"
#include "parka/enum/StatementType.hpp"
#include "parka/ir/AssignmentStatementIr.hpp"
#include "parka/ir/BinaryExpressionIr.hpp"
#include "parka/ir/BlockStatementIr.hpp"
#include "parka/ir/BreakStatementIr.hpp"
#include "parka/ir/CallExpressionIr.hpp"
#include "parka/ir/CastExpressionIr.hpp"
#include "parka/ir/DeclarationStatementIr.hpp"
#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/ExpressionStatementIr.hpp"
#include "parka/ir/ForStatementIr.hpp"
#include "parka/ir/FunctionBodyIr.hpp"
#include "parka/ir/FunctionIr.hpp"
#include "parka/ir/IdentifierExpressionIr.hpp"
#include "parka/ir/ReturnStatementIr.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/BlockSymbolTable.hpp"
#include "parka/symbol/FunctionEntry.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/GlobalSymbolTable.hpp"
#include "parka/symbol/LocalSymbolTable.hpp"
#include "parka/symbol/SymbolTable.hpp"
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

		auto& returnType = ir.prototype().returnType();

		if (returnType != TypeIr::i32Type && returnType != TypeIr::voidType)
		{
			log::error(ast.prototype().returnType()->snippet(), "Entry point `main` must return either $ or $.", TypeIr::i32Type, TypeIr::voidType);
			success = false;
		}

		return success;
	}

	static ExpressionIr* validateCast(const TypeIr& toType, ExpressionIr& expression, SymbolTable& symbolTable)
	{
		const auto& expressionType = expression.type();
		auto conversion = symbolTable.resolveConversion(toType, expressionType);

		if (!conversion)
			return {};

		if (!*conversion)
			return &expression;

		return new CastExpressionIr(expression, **conversion);
	}

	static Result<TypeIr> validateDefaultType(const TypeIr& type)
	{
		// TODO: Optimize?
		if (type == TypeIr::integerType)
			return TypeIr::i32Type;

		if (type == TypeIr::floatType)
			return TypeIr::f64Type;

		// TODO: struct type that can fail

		return type;
	}

	Result<Ir> validateAst(const Ast& ast)
	{
		auto& package = ast.globalPackage();
		auto symbolTable = GlobalSymbolTable(package);
		auto functions = Array<FunctionIr*>();
		auto *entryPoint = (FunctionIr*)nullptr;

		for (auto& entry : symbolTable.functions())
		{
			auto *ir = entry.resolve();

			if (!ir)
				continue;

			if (entry.ast().hasBody())
			{
				auto body = validateFunctionBody(entry.ast().body(), *entry.symbolTable());

				if (body)
					ir->setBody(*body);
			}

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

	FunctionIr *validateFunction(const FunctionAst& ast, FunctionSymbolTable& symbolTable)
	{
		auto prototype = validatePrototype(ast.prototype(), symbolTable);

		if (!prototype)
			return {};

		const auto& name = ast.prototype().identifier().text();
		auto symbol = symbolTable.createSymbol(name);

		return new FunctionIr(std::move(symbol), *prototype, {});
	}

	Result<PrototypeIr> validatePrototype(const PrototypeAst& prototype, FunctionSymbolTable& symbolTable)
	{
		const auto parameterCount = prototype.parameters().length();
		auto parameters = Array<ParameterIr*>(parameterCount);

		for (auto* parameterAst : prototype.parameters())
		{
			auto& entry = symbolTable.declare(*parameterAst);
			auto* parameter = entry.resolve();

			if (!parameter)
				continue;

			parameters.push(parameter);
		}

		auto returnType = TypeIr::voidType;

		if (prototype.returnType())
		{
			auto returnTypeAnnotation = validateTypeAnnotation(*prototype.returnType(), symbolTable);

			if (!returnTypeAnnotation)
				return {};

			returnType = *returnTypeAnnotation;
			symbolTable.setReturnType(returnType);
		}

		symbolTable.setIsExplicitReturnType(!!prototype.returnType());

		if (parameters.length() != prototype.parameters().length())
			return {};

		return PrototypeIr(std::move(parameters), std::move(returnType));
	}

	ParameterIr *validateParameter(const ParameterAst& ast, FunctionSymbolTable& symbolTable)
	{
		auto type = validateTypeAnnotation(ast.annotation(), symbolTable);

		if (!type)
			return {};

		return new ParameterIr(*type);
	}

	Result<ir::FunctionBodyIr> validateFunctionBody(const ast::FunctionBodyAst& ast, FunctionSymbolTable& symbolTable)
	{
		if (ast.isExpression())
		{
			auto* expression = validateExpression(ast.expression(), symbolTable);

			if (!expression)
				return {};

			const auto& returnType = symbolTable.returnType();
			auto* castedValue = validateCast(returnType, *expression, symbolTable);
			
			if (!castedValue)
			{
				log::error(ast.expression().snippet(), "Unable to return `$` in function expecting $.", expression->type(), symbolTable.returnType());
				return {};
			}

			return FunctionBodyIr(*castedValue);
		}

		auto blockStatement = validateBlockStatement(ast.blockStatement(), symbolTable);
		
		if (!blockStatement)
			return {};

		return FunctionBodyIr(*blockStatement);
	}

	VariableIr *validateVariable(const VariableAst& ast, LocalSymbolTable& symbolTable)
	{
		auto identifier = ast.identifier().text();

		if (!ast.annotation())
			return new VariableIr(std::move(identifier), TypeIr(TypeIr::voidType));

		auto annotationType = validateTypeAnnotation(*ast.annotation(), symbolTable);

		if (!annotationType)
			return {};

		return new VariableIr(std::move(identifier), *annotationType);
	}

	Result<TypeIr> validateTypeAnnotation(const TypeAnnotationAst& ast, SymbolTable& symbolTable)
	{
		auto *resolution = symbolTable.resolveSymbol(ast.identifier());

		if (!resolution)
		{
			log::error(ast.identifier().snippet(), "The type `$` could not be found in this scope.", ast.identifier());
			return {};
		}

		auto* typeBase = dynamic_cast<TypeBaseIr*>(resolution);
		
		if (!typeBase)
		{
			// TODO: Figure out what the referred thing was for better clarity
			// TODO: Maybe show "other thing defined here"
			log::error(ast.snippet(), "Expected a type, but `$` was found.", ast.identifier());
			return {};
		}

		return TypeIr(*typeBase);
	}

	StatementIr *validateStatement(const StatementAst& ast, LocalSymbolTable& symbolTable)
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
			{
				auto blockSymbolTable = BlockSymbolTable(symbolTable);

				return validateBlockStatement(static_cast<const BlockStatementAst&>(ast), blockSymbolTable);
			}

			case StatementType::Assignment:
				return validateAssignmentStatement(static_cast<const AssignmentStatementAst&>(ast), symbolTable);

			case StatementType::If:
				return validateIfStatement(static_cast<const ast::IfStatementAst&>(ast), symbolTable);

			default:
				break;
		}

		log::fatal("Unable to validate Statement with TypeIr: $", ast.statementType);
	}

	DeclarationStatementIr *validateDeclarationStatement(const DeclarationStatementAst& ast, LocalSymbolTable& symbolTable)
	{
		// FIXME: Update all expr an stmt validation to FunctionSymbolTable
		auto& entry = symbolTable.declare(ast.variable());
		auto* variable = entry.resolve();
		auto* value = validateExpression(ast.value(), symbolTable);

		if (!variable || !value)
			return {};

		const auto& valueType = value->type();

		if (!ast.variable().annotation())
		{
			auto variableType = validateDefaultType(valueType);

			if (!variableType)
				return {};
			
			variable->setType(*variableType);
		}

		auto* castedValue = validateCast(variable->type(), *value, symbolTable);
		
		if (!castedValue)
			log::fatal(ast.snippet(), "Unable to find conversion conversion from `$` to `$`. This should never happen.", value->type(), variable->type());


		return new DeclarationStatementIr(*variable, *castedValue);
	}

	ExpressionStatementIr* validateExpressionStatement(const ExpressionStatementAst& ast, LocalSymbolTable& symbolTable)
	{
		auto* expression = validateExpression(ast.expression(), symbolTable);

		if (!expression)
			return {};

		return new ExpressionStatementIr(*expression);
	}

	AssignmentStatementIr *validateAssignmentStatement(const AssignmentStatementAst& ast, LocalSymbolTable& symbolTable)
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
		auto* op = symbolTable.resolveAssignmentOperator(lhs->type(), value->type(), ast.assignmentType());

		if (!op)
		{
			log::error(ast.snippet(), "No assignment operator `$ $ $` has been defined.", lhs->type(), ast.assignmentType(), value->type());
			return {};
		}

		return new AssignmentStatementIr(identifier, *value, *op);
	}

	ReturnStatementIr *validateReturnStatement(const ReturnStatementAst& ast, LocalSymbolTable& symbolTable)
	{
		if (!ast.hasValue())
		{
			if (symbolTable.returnType() == TypeIr::voidType)
				return new ReturnStatementIr();

			log::error(ast.snippet(), "Expected $ return value but none was given.", symbolTable.returnType());
			return {};
		}

		auto* value = validateExpression(ast.value(), symbolTable);

		if (!value)
			return {};

		auto* castedValue = validateCast(symbolTable.returnType(), *value, symbolTable);

		if (!castedValue)
		{
			// TODO: Highlight function return type
			log::error(ast.value().snippet(), "Unable to return $ in function expecting $.", value->type(), symbolTable.returnType());
			return {};
		}
		
		return new ReturnStatementIr(*castedValue);
	}

	BreakStatementIr *validateBreakStatement(const BreakStatementAst& ast, LocalSymbolTable& symbolTable)
	{
		if (!symbolTable.isInLoop())
		{
			log::error(ast.snippet(), "A break statement may only be put inside of a loop.");
			return {};
		}

		return new BreakStatementIr();
	}

	ContinueStatementIr *validateContinueStatement(const ContinueStatementAst& ast, LocalSymbolTable& symbolTable)
	{
		if (!symbolTable.isInLoop())
		{
			log::error(ast.snippet(), "A continue statement may only be put inside of a loop.");
			return {};
		}

		return new ContinueStatementIr();
	}

	YieldStatementIr *validateYieldStatement(const YieldStatementAst&, LocalSymbolTable&)
	{
		// Must be in an block/if statement
		log::notImplemented(here());
	}

	ForStatementIr *validateForStatement(const ForStatementAst& ast, LocalSymbolTable& symbolTable)
	{
		auto* declaration = validateDeclarationStatement(ast.declaration(), symbolTable);

		if (!declaration)
			return {};

		auto* condition = validateExpression(ast.condition(), symbolTable);
		auto* action = validateStatement(ast.action(), symbolTable);
		auto blockSymbolTable = BlockSymbolTable(symbolTable);

		blockSymbolTable.setInLoop();

		auto* body = validateBlockStatement(ast.body(), blockSymbolTable);

		if (!condition  || !action || !body)
			return {};

		auto* castedValue = validateCast(TypeIr::boolType, *condition, symbolTable);

		if (!castedValue)
		{
			log::error(ast.condition().snippet(), "Expression could not be converted from `$` to `$`.", condition->type(), TypeIr::boolType);
			return {};
		}

		return new ForStatementIr(*declaration, *castedValue, *action, *body);
	}

	BlockStatementIr *validateBlockStatement(const BlockStatementAst& ast, LocalSymbolTable& symbolTable)
	{
		auto& statementAsts = ast.statements();
		auto statementIrs = Array<StatementIr*>(statementAsts.length());

		for (const auto *statement : statementAsts)
		{
			auto *ir = validateStatement(*statement, symbolTable);

			if (!ir)
				continue;

			statementIrs.push(ir);
		}

		if (statementIrs.length() != statementAsts.length())
			return {};

		return new BlockStatementIr(std::move(statementIrs));
	}
	
	IfStatementIr* validateIfStatement(const IfStatementAst& ast, LocalSymbolTable& symbolTable)
	{
		auto* condition = validateExpression(ast.condition(), symbolTable);
		auto* thenCase = validateStatement(ast.thenCase(), symbolTable);
		auto* elseCase = ast.hasElseCase()
			? validateStatement(ast.elseCase(), symbolTable)
			: nullptr;

		if (!condition || !thenCase || (ast.hasElseCase() && !elseCase))
			return {};

		auto* castedValue = validateCast(TypeIr::boolType, *condition, symbolTable);

		if (!castedValue)
		{
			log::error(ast.condition().snippet(), "Unable to use expression of type $ as if condition.", condition->type());
			return {};
		}

		return new IfStatementIr(*castedValue, *thenCase, elseCase);
	}

	ExpressionIr* validateExpression(const ExpressionAst& ast, LocalSymbolTable& symbolTable)
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

			case ExpressionType::Subscript:
				break;

			case ExpressionType::MemberAccess:
				break;

			case ExpressionType::Prefix:
				break;

			case ExpressionType::Cast:
				return validateCastExpression(static_cast<const CastExpressionAst&>(ast), symbolTable);

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

		log::fatal("Unable to validate Expression with TypeIr: $", ast.expressionType);
	}

	BinaryExpressionIr* validateBinaryExpression(const BinaryExpressionAst& ast, LocalSymbolTable& symbolTable)
	{
		auto *lhs = validateExpression(ast.lhs(), symbolTable);
		auto *rhs = validateExpression(ast.rhs(), symbolTable);

		if (!lhs || !rhs)
			return {};

		const auto& lhsType = lhs->type();
		const auto& rhsType = rhs->type();
		auto *op = symbolTable.resolveBinaryOperator(ast.binaryExpressionType(), lhsType, rhsType);

		if (!op)
		{
			log::error(ast.snippet(), "No operator `$ $ $` has been defined.", lhsType, ast.binaryExpressionType(), rhsType);
			return {};
		}

		auto result = new BinaryExpressionIr(*lhs, *rhs, *op);

		return result;
	}

	CallExpressionIr* validateCallExpression(const CallExpressionAst& ast, LocalSymbolTable& symbolTable)
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

			auto* castedValue = validateCast(parameter.type(), *value, symbolTable);

			if (!castedValue)
			{
				log::error(valueAst.snippet(), "Parameter $ calls for $ but $ was passed in.", parameter.symbol(), parameter.type(), value->type());
				continue;
			}

			arguments.push(ArgumentIr(*castedValue));
		}
		
		if (arguments.length() != ast.arguments().length())
			return {};

		return new CallExpressionIr(function, std::move(arguments));
	}

	IdentifierExpressionIr* validateIdentifierExpression(const IdentifierExpressionAst& ast, LocalSymbolTable& symbolTable)
	{
		auto *result = symbolTable.resolveSymbol(ast.identifier());

		if (!result)
		{
			log::error(ast.snippet(), "No definition for `$` could be found in this scope.", ast.identifier());
			return {};
		}

		return new IdentifierExpressionIr(*result);
	}

	ExpressionIr* validateCastExpression(const CastExpressionAst& ast, LocalSymbolTable& symbolTable)
	{
		auto* expression = validateExpression(ast.expression(), symbolTable);
		auto type = validateTypeAnnotation(ast.typeAnnotation(), symbolTable);

		if (!expression || !type)
			return {};

		auto* castedValue = validateCast(*type, *expression, symbolTable);

		if (!castedValue)
		{
			log::error(ast.snippet(), "Expression with value `$` cannot be casted to `$`.", expression->type(), *type);
			return {};
		}

		return castedValue;
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

	IntegerLiteralIr* validateIntegerLiteral(const IntegerLiteralAst& ast)
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

	FloatLiteralIr* validateFloatLiteral(const FloatLiteralAst& ast)
	{
		// TODO: handle type suffixes to determine f64 vs f32
		auto value = parseDecimal(ast.snippet());

		return new FloatLiteralIr(value);
	}

	StringLiteralIr* validateStringLiteral(const StringLiteralAst& ast)
	{
		// TODO: Handle escapes
		const auto& snippet = ast.snippet();
		auto text = snippet.substr(1, snippet.length() - 2);
		auto *context = new StringLiteralIr(std::move(text));

		return context;
	}

	CharLiteralIr* validateCharLiteral(const CharLiteralAst& ast)
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

	BoolLiteralIr* validateBoolLiteral(const BoolLiteralAst& ast)
	{
		return new BoolLiteralIr(ast.value());
	}
}
