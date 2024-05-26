#include "parka/validation/Validator.hpp"
#include "parka/ast/AssignmentStatementAst.hpp"
#include "parka/ast/CallExpressionAst.hpp"
#include "parka/ast/ConditionalExpressionAst.hpp"
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
#include "parka/ir/BoolPrimitiveIr.hpp"
#include "parka/ir/BreakStatementIr.hpp"
#include "parka/ir/CallExpressionIr.hpp"
#include "parka/ir/CastExpressionIr.hpp"
#include "parka/ir/ConditionalExpressionIr.hpp"
#include "parka/ir/DeclarationStatementIr.hpp"
#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/ExpressionStatementIr.hpp"
#include "parka/ir/FloatPrimitiveIr.hpp"
#include "parka/ir/ForStatementIr.hpp"
#include "parka/ir/FunctionBodyIr.hpp"
#include "parka/ir/FunctionIr.hpp"
#include "parka/ir/I32PrimitiveIr.hpp"
#include "parka/ir/IdentifierExpressionIr.hpp"
#include "parka/ir/IntegerPrimitiveIr.hpp"
#include "parka/ir/ReturnStatementIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/VoidPrimitiveIr.hpp"
#include "parka/log/Log.hpp"
#include "parka/validation/BlockContext.hpp"
#include "parka/validation/FunctionEntry.hpp"
#include "parka/validation/FunctionContext.hpp"
#include "parka/validation/GlobalContext.hpp"
#include "parka/validation/LocalContext.hpp"
#include "parka/validation/Context.hpp"
#include "parka/validation/VariableEntry.hpp"
#include "parka/util/Array.hpp"

namespace parka::validation
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

	// static bool validatePackage(Array<FunctionIr*>& functions, PackageContext& context)
	// {
	// 	bool success = true;

	// 	if (!validateFunctions(functions, context.functions()))
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

		if (&returnType != &I32PrimitiveIr::instance && &returnType != &VoidPrimitiveIr::voidPrimitive)
		{
			log::error(ast.prototype().returnType()->snippet(), "Entry point `main` must return either $ or $.", I32PrimitiveIr::instance, VoidPrimitiveIr::voidPrimitive);
			success = false;
		}

		return success;
	}

	static ExpressionIr* validateCast(const TypeIr& toType, ExpressionIr& expression, Context& context)
	{
		const auto& expressionType = expression.type();

		if (&toType == &expressionType)
			return &expression;

		auto* conversion = expressionType.getConversion(toType);

		if (!conversion)
			return {};

		return new CastExpressionIr(expression, *conversion);
	}

	static const TypeIr* validateDefaultType(const TypeIr& type)
	{
		// TODO: Optimize?
		if (&type == &IntegerPrimitiveIr::instance)
			return &I32PrimitiveIr::instance;

		// if (&type == &FloatPrimitiveIr::floatPrimitive)
		// 	return &FloatPrimitiveIr::f64Primitive;

		// TODO: struct type that can fail

		return &type;
	}

	Result<Ir> validateAst(const Ast& ast)
	{
		auto& package = ast.globalPackage();
		auto context = GlobalContext(package);
		auto functions = Array<FunctionIr*>();
		auto *entryPoint = (FunctionIr*)nullptr;

		for (auto& entry : context.functions())
		{
			auto *ir = entry.resolve();

			if (!ir)
				continue;

			if (entry.ast().hasBody())
			{
				auto body = validateFunctionBody(entry.ast().body(), *entry.context());

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

	FunctionIr *validateFunction(const FunctionAst& ast, FunctionContext& context)
	{
		auto prototype = validatePrototype(ast.prototype(), context);

		if (!prototype)
			return {};

		const auto& name = ast.prototype().identifier().text();
		auto symbol = context.createSymbol(name);

		return new FunctionIr(std::move(symbol), *prototype, {});
	}

	Result<PrototypeIr> validatePrototype(const PrototypeAst& prototype, FunctionContext& context)
	{
		const auto parameterCount = prototype.parameters().length();
		auto parameters = Array<ParameterIr*>(parameterCount);

		for (auto* parameterAst : prototype.parameters())
		{
			auto& entry = context.declare(*parameterAst);
			auto* parameter = entry.resolve();

			if (!parameter)
				continue;

			parameters.push(parameter);
		}

		const auto* returnType = (TypeIr*)&VoidPrimitiveIr::voidPrimitive;

		if (prototype.returnType())
		{
			auto returnTypeAnnotation = validateTypeAnnotation(*prototype.returnType(), context);

			if (!returnTypeAnnotation)
				return {};

			returnType = returnTypeAnnotation;

			context.setReturnType(*returnType);
		}

		context.setIsExplicitReturnType(!!prototype.returnType());

		if (parameters.length() != prototype.parameters().length())
			return {};

		return PrototypeIr(std::move(parameters), *returnType);
	}

	ParameterIr *validateParameter(const ParameterAst& ast, FunctionContext& context)
	{
		auto type = validateTypeAnnotation(ast.annotation(), context);

		if (!type)
			return {};

		return new ParameterIr(*type);
	}

	Result<ir::FunctionBodyIr> validateFunctionBody(const ast::FunctionBodyAst& ast, FunctionContext& context)
	{
		if (ast.isExpression())
		{
			auto* expression = validateExpression(ast.expression(), context);

			if (!expression)
				return {};

			const auto& returnType = context.returnType();
			auto* castedValue = validateCast(returnType, *expression, context);
			
			if (!castedValue)
			{
				log::error(ast.expression().snippet(), "Unable to return `$` in function expecting $.", expression->type(), context.returnType());
				return {};
			}

			return FunctionBodyIr(*castedValue);
		}

		auto blockStatement = validateBlockStatement(ast.blockStatement(), context);
		
		if (!blockStatement)
			return {};

		return FunctionBodyIr(*blockStatement);
	}

	VariableIr *validateVariable(const VariableAst& ast, LocalContext& context)
	{
		auto identifier = ast.identifier().text();

		if (!ast.annotation())
			return new VariableIr(std::move(identifier), VoidPrimitiveIr::voidPrimitive);

		auto annotationType = validateTypeAnnotation(*ast.annotation(), context);

		if (!annotationType)
			return {};

		return new VariableIr(std::move(identifier), *annotationType);
	}

	const TypeIr* validateTypeAnnotation(const TypeAnnotationAst& ast, Context& context)
	{
		auto *resolution = context.resolveSymbol(ast.identifier());

		if (!resolution)
		{
			log::error(ast.identifier().snippet(), "The type `$` could not be found in this scope.", ast.identifier());
			return {};
		}

		auto* type = dynamic_cast<TypeIr*>(resolution);
		
		if (!type)
		{
			// TODO: Figure out what the referred thing was for better clarity
			// TODO: Maybe show "other thing defined here"
			log::error(ast.snippet(), "Expected a type, but `$` was found.", ast.identifier());
			return {};
		}

		return type;
	}

	StatementIr *validateStatement(const StatementAst& ast, LocalContext& context)
	{
		switch (ast.statementType)
		{
			case StatementType::Declaration:
				return validateDeclarationStatement(static_cast<const DeclarationStatementAst&>(ast), context);

			case StatementType::Expression:
				return validateExpressionStatement(static_cast<const ExpressionStatementAst&>(ast), context);

			case StatementType::Return:
				return validateReturnStatement(static_cast<const ReturnStatementAst&>(ast), context);

			case StatementType::Break:
				return validateBreakStatement(static_cast<const BreakStatementAst&>(ast), context);

			case StatementType::Continue:
				return validateContinueStatement(static_cast<const ContinueStatementAst&>(ast), context);

			case StatementType::Yield:
				return validateYieldStatement(static_cast<const YieldStatementAst&>(ast), context);

			case StatementType::For:
				return validateForStatement(static_cast<const ForStatementAst&>(ast), context);

			case StatementType::Block:
			{
				auto blockContext = BlockContext(context);

				return validateBlockStatement(static_cast<const BlockStatementAst&>(ast), blockContext);
			}

			case StatementType::Assignment:
				return validateAssignmentStatement(static_cast<const AssignmentStatementAst&>(ast), context);

			case StatementType::If:
				return validateIfStatement(static_cast<const ast::IfStatementAst&>(ast), context);

			default:
				break;
		}

		log::fatal("Unable to validate Statement with TypeIr: $", ast.statementType);
	}

	DeclarationStatementIr *validateDeclarationStatement(const DeclarationStatementAst& ast, LocalContext& context)
	{
		// FIXME: Update all expr an stmt validation to FunctionContext
		auto& entry = context.declare(ast.variable());
		auto* variable = entry.resolve();
		auto* value = validateExpression(ast.value(), context);

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

		auto* castedValue = validateCast(variable->type(), *value, context);
		
		if (!castedValue)
			log::fatal(ast.snippet(), "Unable to find conversion conversion from `$` to `$`. This indicates a bug in validation code.", value->type(), variable->type());

		return new DeclarationStatementIr(*variable, *castedValue);
	}

	ExpressionStatementIr* validateExpressionStatement(const ExpressionStatementAst& ast, LocalContext& context)
	{
		auto* expression = validateExpression(ast.expression(), context);

		if (!expression)
			return {};

		return new ExpressionStatementIr(*expression);
	}

	AssignmentStatementIr *validateAssignmentStatement(const AssignmentStatementAst& ast, LocalContext& context)
	{
		log::notImplemented(here());
		// auto* lhs = validateExpression(ast.identifier(), context);
		// auto* value = validateExpression(ast.value(), context);

		// if (!lhs || !value)
		// 	return {};
		
		// if (lhs->expressionType != ExpressionType::Identifier)
		// {
		// 	log::error(ast.identifier().snippet(), "Expected LValue. This expression is not a modifiable value.");
		// 	return {};
		// }

		// auto& identifier = static_cast<IdentifierExpressionIr&>(*lhs);
		// auto* op = context.resolveAssignmentOperator(lhs->type(), value->type(), ast.assignmentType());

		// if (!op)
		// {
		// 	log::error(ast.snippet(), "No assignment operator `$ $ $` has been defined.", lhs->type(), ast.assignmentType(), value->type());
		// 	return {};
		// }

		// return new AssignmentStatementIr(identifier, *value, *op);
	}

	ReturnStatementIr *validateReturnStatement(const ReturnStatementAst& ast, LocalContext& context)
	{
		if (!ast.hasValue())
		{
			if (&context.returnType() == &VoidPrimitiveIr::voidPrimitive)
				return new ReturnStatementIr();

			log::error(ast.snippet(), "Expected $ return value but none was given.", context.returnType());
			return {};
		}

		auto* value = validateExpression(ast.value(), context);

		if (!value)
			return {};

		auto* castedValue = validateCast(context.returnType(), *value, context);

		if (!castedValue)
		{
			// TODO: Highlight function return type
			log::error(ast.value().snippet(), "Unable to return $ in function expecting $.", value->type(), context.returnType());
			return {};
		}
		
		return new ReturnStatementIr(*castedValue);
	}

	BreakStatementIr *validateBreakStatement(const BreakStatementAst& ast, LocalContext& context)
	{
		if (!context.isInLoop())
		{
			log::error(ast.snippet(), "A break statement may only be put inside of a loop.");
			return {};
		}

		return new BreakStatementIr();
	}

	ContinueStatementIr *validateContinueStatement(const ContinueStatementAst& ast, LocalContext& context)
	{
		if (!context.isInLoop())
		{
			log::error(ast.snippet(), "A continue statement may only be put inside of a loop.");
			return {};
		}

		return new ContinueStatementIr();
	}

	YieldStatementIr *validateYieldStatement(const YieldStatementAst&, LocalContext&)
	{
		// Must be in an block/if statement
		log::notImplemented(here());
	}

	ForStatementIr *validateForStatement(const ForStatementAst& ast, LocalContext& context)
	{
		auto* declaration = validateDeclarationStatement(ast.declaration(), context);

		if (!declaration)
			return {};

		auto* condition = validateExpression(ast.condition(), context);
		auto* action = validateStatement(ast.action(), context);
		auto blockContext = BlockContext(context);

		blockContext.setInLoop();

		auto* body = validateBlockStatement(ast.body(), blockContext);

		if (!condition  || !action || !body)
			return {};

		auto* castedValue = validateCast(BoolPrimitiveIr::boolPrimitive, *condition, context);

		if (!castedValue)
		{
			log::error(ast.condition().snippet(), "Expression could not be converted from `$` to `$`.", condition->type(), BoolPrimitiveIr::boolPrimitive);
			return {};
		}

		return new ForStatementIr(*declaration, *castedValue, *action, *body);
	}

	BlockStatementIr *validateBlockStatement(const BlockStatementAst& ast, LocalContext& context)
	{
		auto& statementAsts = ast.statements();
		auto statementIrs = Array<StatementIr*>(statementAsts.length());

		for (const auto *statement : statementAsts)
		{
			auto *ir = validateStatement(*statement, context);

			if (!ir)
				continue;

			statementIrs.push(ir);
		}

		if (statementIrs.length() != statementAsts.length())
			return {};

		return new BlockStatementIr(std::move(statementIrs));
	}
	
	IfStatementIr* validateIfStatement(const IfStatementAst& ast, LocalContext& context)
	{
		auto* condition = validateExpression(ast.condition(), context);
		auto* thenCase = validateStatement(ast.thenCase(), context);
		auto* elseCase = ast.hasElseCase()
			? validateStatement(ast.elseCase(), context)
			: nullptr;

		if (!condition || !thenCase || (ast.hasElseCase() && !elseCase))
			return {};

		auto* castedValue = validateCast(BoolPrimitiveIr::boolPrimitive, *condition, context);

		if (!castedValue)
		{
			log::error(ast.condition().snippet(), "Unable to use expression of type $ as if condition.", condition->type());
			return {};
		}

		return new IfStatementIr(*castedValue, *thenCase, elseCase);
	}

	ExpressionIr* validateExpression(const ExpressionAst& ast, LocalContext& context)
	{
		switch (ast.expressionType)
		{
			case ExpressionType::Binary:
				return validateBinaryExpression(static_cast<const BinaryExpressionAst&>(ast), context);

			case ExpressionType::Call:
				return validateCallExpression(static_cast<const CallExpressionAst&>(ast), context);

			case ExpressionType::Conditional:
				return validateConditionalExpression(static_cast<const ConditionalExpressionAst&>(ast), context);

			case ExpressionType::Identifier:
				return validateIdentifierExpression(static_cast<const IdentifierExpressionAst&>(ast), context);

			case ExpressionType::Subscript:
				break;

			case ExpressionType::MemberAccess:
				break;

			case ExpressionType::Prefix:
				break;

			case ExpressionType::Cast:
				return validateCastExpression(static_cast<const CastExpressionAst&>(ast), context);

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

	BinaryExpressionIr* validateBinaryExpression(const BinaryExpressionAst& ast, LocalContext& context)
	{
		auto *lhs = validateExpression(ast.lhs(), context);
		auto *rhs = validateExpression(ast.rhs(), context);

		if (!lhs || !rhs)
			return {};

		const auto& lhsType = lhs->type();
		const auto& rhsType = rhs->type();

		auto* op = lhsType.getBinaryOperator(ast.binaryExpressionType(), rhsType);

		if (!op)
		{
			log::error(ast.snippet(), "No operator `$ $ $` has been defined.", lhsType, ast.binaryExpressionType(), rhsType);
			return {};
		}

		auto result = new BinaryExpressionIr(*lhs, *rhs, *op);

		return result;
	}

	CallExpressionIr* validateCallExpression(const CallExpressionAst& ast, LocalContext& context)
	{
		auto* subject = validateExpression(ast.subject(), context);

		if (!subject)
			return {};

		// TODO: Implement call expression operators

		log::notImplemented(here());

		// if (subject->expressionType != ExpressionType::Identifier)
		// {
		// 	log::error(ast.subject().snippet(), "Unable to call expression as function.");
		// 	return {};
		// }

		// auto& reference = static_cast<IdentifierExpressionIr&>(*subject);
		// auto& lvalue = reference.value();

		// if (lvalue.resolvableType != ResolvableType::Function)
		// {
		// 	log::error(ast.subject().snippet(), "Unable to call $ as function.", lvalue.resolvableType);
		// 	return {};
		// }

		// auto& function = static_cast<const FunctionIr&>(lvalue);
		// auto& prototype = function.prototype();

		// if (prototype.parameters().length() != ast.arguments().length())
		// {
		// 	log::error(ast.snippet(), "This function takes $ argument(s) but $ were given.", prototype.parameters().length(), ast.arguments().length());
		// 	return {};
		// }

		// auto arguments = Array<ArgumentIr>(ast.arguments().length());

		// for (usize i = 0; i < ast.arguments().length(); ++i)
		// {
		// 	auto& valueAst = *ast.arguments()[i];
		// 	auto& parameter = *prototype.parameters()[i];
		// 	auto* value = validateExpression(valueAst, context);

		// 	if (!value)
		// 		continue;

		// 	auto* castedValue = validateCast(parameter.type(), *value, context);

		// 	if (!castedValue)
		// 	{
		// 		log::error(valueAst.snippet(), "Parameter $ calls for $ but $ was passed in.", parameter.symbol(), parameter.type(), value->type());
		// 		continue;
		// 	}

		// 	arguments.push(ArgumentIr(*castedValue));
		// }
		
		// if (arguments.length() != ast.arguments().length())
		// 	return {};

		// return new CallExpressionIr(function, std::move(arguments));
	}

	ir::ConditionalExpressionIr* validateConditionalExpression(const ast::ConditionalExpressionAst& ast, LocalContext& context)
	{
		auto* condition = validateExpression(ast.condition(), context);
		auto* thenCase = validateExpression(ast.thenCase(), context);
		auto* elseCase = validateExpression(ast.elseCase(), context);

		if (!condition || !thenCase || !elseCase)
			return {};

		auto* castedCondition = validateCast(BoolPrimitiveIr::boolPrimitive, *condition, context);

		if (!castedCondition)
		{
			log::error(ast.condition().snippet(), "Condition is not of type `$`.", BoolPrimitiveIr::boolPrimitive);
			return {};
		}

		auto* castedElseCase = validateCast(thenCase->type(), *elseCase, context);

		if (castedElseCase)
			return new ConditionalExpressionIr(*castedCondition, *thenCase, *castedElseCase);

		auto *castedThenCase = validateCast(elseCase->type(), *thenCase, context);

		if (castedThenCase)
			return new ConditionalExpressionIr(*castedCondition, *castedThenCase, *elseCase);

		log::error(ast.snippet(), "Then case and else case are of incompatible types.");

		return {};
	}

	IdentifierExpressionIr* validateIdentifierExpression(const IdentifierExpressionAst& ast, LocalContext& context)
	{
		auto *result = context.resolveSymbol(ast.identifier());

		if (!result)
		{
			log::error(ast.snippet(), "No definition for `$` could be found in this scope.", ast.identifier());
			return {};
		}

		return new IdentifierExpressionIr(*result);
	}

	ExpressionIr* validateCastExpression(const CastExpressionAst& ast, LocalContext& context)
	{
		auto* expression = validateExpression(ast.expression(), context);
		auto type = validateTypeAnnotation(ast.typeAnnotation(), context);

		if (!expression || !type)
			return {};

		auto* castedValue = validateCast(*type, *expression, context);

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
