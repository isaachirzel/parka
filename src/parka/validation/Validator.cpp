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
#include "parka/enum/EntityType.hpp"
#include "parka/enum/ExpressionType.hpp"
#include "parka/enum/PrimitiveType.hpp"
#include "parka/enum/StatementType.hpp"
#include "parka/ir/AssignmentStatementIr.hpp"
#include "parka/ir/BinaryExpressionIr.hpp"
#include "parka/ir/BlockStatementIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/BreakStatementIr.hpp"
#include "parka/ir/CallExpressionIr.hpp"
#include "parka/ir/CastExpressionIr.hpp"
#include "parka/ir/ConditionalExpressionIr.hpp"
#include "parka/ir/DeclarationStatementIr.hpp"
#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/ExpressionStatementIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/ForStatementIr.hpp"
#include "parka/ir/FunctionBodyIr.hpp"
#include "parka/ir/FunctionIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/IdentifierExpressionIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/ReturnStatementIr.hpp"
#include "parka/ir/StructIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
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

	/*
	validation lock:

		auto readLock = shared_lock(mutex);

		if (validated)
			return context;

		readLock.unlock();

		auto writeLock = unique_lock(mutex, std::defer_lock_t);

		if (writeLock.try_lock())
		{
			context = syntax.validate(context);
			validated = true;

			return context;
		}

	*/

	static bool validateEntryPoint(const ir::FunctionIr& ir, const ast::FunctionAst& ast)
	{
		bool success = true;
		if (ir.prototype().parameters().length() > 0)
		{
			const auto& parameters = ast.prototype().parameters();
			auto& first = *parameters.front();
			auto& last = *parameters.back();
			auto snippet = first.snippet() + last.snippet();

			log::entryPointNoParametersAllowedError(snippet);
			success = false;
		}

		auto& returnType = ir.prototype().returnType();

		if (&returnType != &PrimitiveIr::i32Primitive && &returnType != &PrimitiveIr::voidPrimitive)
		{
			log::entryPointReturnTypeError(ast.prototype().returnType()->snippet(), returnType);
			success = false;
		}

		return success;
	}

	static ExpressionIr* validateImplicitCast(const TypeIr& toType, ExpressionIr& expression, Context& context)
	{
		const auto& expressionType = expression.type();

		if (toType == expressionType)
			return &expression;

		auto& typeContext = context.globalContext().getTypeContext(expressionType);
		auto* cast = typeContext.getImplicitCastTo(toType);

		if (!cast)
			return {};

		return new CastExpressionIr(expression, *cast);
	}

	static const TypeIr* validateDefaultType(const TypeIr& type)
	{
		if (type == PrimitiveIr::integerPrimitive)
			return &PrimitiveIr::i32Primitive;

		if (&type == &PrimitiveIr::floatPrimitive)
			return &PrimitiveIr::f64Primitive;

		// TODO: struct literal that fails

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
					ir->body() = *body;
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
		// validate function sets up the symbol and prototype, the body is handled later
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

		const auto* returnType = (TypeIr*)&PrimitiveIr::voidPrimitive;

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

		return new ParameterIr(String(ast.snippet().ptr(), ast.snippet().length()), *type);
	}

	Result<ir::FunctionBodyIr> validateFunctionBody(const ast::FunctionBodyAst& ast, FunctionContext& context)
	{
		if (ast.isExpression())
		{
			auto* expression = validateExpression(ast.expression(), context);

			if (!expression)
				return {};

			const auto& returnType = context.returnType();
			auto* castedValue = validateImplicitCast(returnType, *expression, context);
			
			if (!castedValue)
			{
				log::invalidReturnValueError(ast.expression().snippet(), expression->type(), context.returnType());
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
			return new VariableIr(std::move(identifier), PrimitiveIr::voidPrimitive);

		auto annotationType = validateTypeAnnotation(*ast.annotation(), context);

		if (!annotationType)
			return {};

		return new VariableIr(std::move(identifier), *annotationType);
	}

	const TypeIr* validateTypeAnnotation(const TypeAnnotationAst& ast, Context& context)
	{
		auto *entity = context.resolveSymbol(ast.identifier());

		if (!entity)
		{
			log::undefinedEntityError(ast.identifier());
			return {};
		}

		switch (entity->entityType)
		{
			case EntityType::Primitive:
				return static_cast<PrimitiveIr*>(entity);

			case EntityType::Struct:
				return static_cast<StructIr*>(entity);

			default:
				log::typeAnnotationError(ast.snippet(), *entity);
				break;
		}

		return {};
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
		}

		abort();
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

		auto* castedValue = validateImplicitCast(variable->type(), *value, context);
		
		if (!castedValue)
		{
			log::initializationTypeError(ast.value().snippet(), *variable, value->type());
			return {};
		}

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
		auto* lhs = validateExpression(ast.identifier(), context);
		auto* value = validateExpression(ast.value(), context);

		if (!lhs || !value)
			return {};
		
		if (lhs->expressionType != ExpressionType::Identifier)
		{
			log::lValueError(ast.identifier().snippet());
			return {};
		}

		auto& identifier = static_cast<IdentifierExpressionIr&>(*lhs);
		auto& leftType = identifier.type();
		auto& valueType = value->type();
		auto& typeContext = context.globalContext().getTypeContext(leftType);
		auto* op = typeContext.getAssignmentOperator(ast.assignmentType(), valueType);

		if (!op)
		{
			log::undefinedAssignmentOperatorError(ast.snippet(), lhs->type(), ast.assignmentType(), value->type());
			return {};
		}

		return new AssignmentStatementIr(identifier, *value, *op);
	}

	ReturnStatementIr *validateReturnStatement(const ReturnStatementAst& ast, LocalContext& context)
	{
		if (!ast.hasValue())
		{
			if (&context.returnType() == &PrimitiveIr::voidPrimitive)
				return new ReturnStatementIr();

			log::missingReturnValueError(ast.snippet(), context.returnType());			
			return {};
		}

		auto* value = validateExpression(ast.value(), context);

		if (!value)
			return {};

		auto* castedValue = validateImplicitCast(context.returnType(), *value, context);

		if (!castedValue)
		{
			log::invalidReturnValueError(ast.value().snippet(), value->type(), context.returnType());
			return {};
		}
		
		return new ReturnStatementIr(*castedValue);
	}

	BreakStatementIr *validateBreakStatement(const BreakStatementAst& ast, LocalContext& context)
	{
		if (!context.isInLoop())
		{
			log::invalidBreakError(ast.snippet());
			return {};
		}

		return new BreakStatementIr();
	}

	ContinueStatementIr *validateContinueStatement(const ContinueStatementAst& ast, LocalContext& context)
	{
		if (!context.isInLoop())
		{
			log::invalidContinueError(ast.snippet());
			return {};
		}

		return new ContinueStatementIr();
	}

	YieldStatementIr *validateYieldStatement(const YieldStatementAst&, LocalContext&)
	{
		// Must be in an block/if statement
		notImplemented();
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

		if (condition->type() != ir::PrimitiveIr::boolPrimitive)
		{
			log::typeMismatchError(ast.condition().snippet(), condition->type(), PrimitiveIr::boolPrimitive);
			return {};
		}

		return new ForStatementIr(*declaration, *condition, *action, *body);
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

		if (condition->type() != PrimitiveIr::boolPrimitive)
		{
			log::typeMismatchError(ast.condition().snippet(), condition->type(), PrimitiveIr::boolPrimitive);
			return {};
		}

		return new IfStatementIr(*condition, *thenCase, elseCase);
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
		}

		log::fatal("Unable to validate expression with type: $.", ast.expressionType);
	}

	BinaryExpressionIr* validateBinaryExpression(const BinaryExpressionAst& ast, LocalContext& context)
	{
		auto *lhs = validateExpression(ast.lhs(), context);
		auto *rhs = validateExpression(ast.rhs(), context);

		if (!lhs || !rhs)
			return {};

		const auto& lhsType = lhs->type();
		const auto& rhsType = rhs->type();

		auto& typeContext = context.globalContext().getTypeContext(lhsType);
		auto* op = typeContext.getBinaryOperator(ast.binaryExpressionType(), rhsType);

		if (!op)
		{
			log::undefinedBinaryOperatorError(ast.snippet(), lhsType, ast.binaryExpressionType(), rhsType);
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

		auto* entity = subject->expressionType == ExpressionType::Identifier
			? &static_cast<IdentifierExpressionIr&>(*subject).entity()
			: nullptr;

		if (!entity || entity->entityType != EntityType::Function)
		{
			log::invalidFunctionCallError(ast.subject().snippet(), subject->type());
			return {};
		}

		auto& function = static_cast<const ir::FunctionIr&>(*entity);
		auto arguments = Array<ExpressionIr*>(ast.arguments().length());
		auto argumentCount = ast.arguments().length();

		for (usize i = 0; i < argumentCount; ++i)
		{
			auto& argumentAst = *ast.arguments()[i];
			auto* argumentIr = validateExpression(argumentAst, context);

			if (!argumentIr)
				continue;

			arguments.push(argumentIr);
		}
		
		if (arguments.length() != ast.arguments().length())
			return {};

		auto success = true;
		auto parameterCount = function.prototype().parameters().length();

		if (argumentCount > parameterCount)
		{
			log::tooManyArgumentsError(ast.snippet());
			success = false;
		}

		if (parameterCount > argumentCount)
		{
			log::tooFewArgumentsError(ast.snippet());
			success = false;
		}

		auto iterCount = argumentCount > parameterCount
			? parameterCount
			: argumentCount;

		for (usize i = 0; i < iterCount; ++i)
		{
			auto& argument = *arguments[i];
			auto& parameter = *function.prototype().parameters()[i];
			auto* castedArgument = validateImplicitCast(parameter.type(), argument, context);

			if (!castedArgument)
			{
				log::typeMismatchError(ast.arguments()[i]->snippet(), argument.type(), parameter.type());
				success = false;
				continue;
			}

			arguments[i] = castedArgument;
		}

		if (!success)
			return {};

		return new CallExpressionIr(function, std::move(arguments));
	}

	ir::ConditionalExpressionIr* validateConditionalExpression(const ast::ConditionalExpressionAst& ast, LocalContext& context)
	{
		auto* condition = validateExpression(ast.condition(), context);
		auto* thenCase = validateExpression(ast.thenCase(), context);
		auto* elseCase = validateExpression(ast.elseCase(), context);

		if (!condition || !thenCase || !elseCase)
			return {};

		if (condition->type() != PrimitiveIr::boolPrimitive)
		{
			log::typeMismatchError(ast.condition().snippet(), condition->type(), PrimitiveIr::boolPrimitive);
			return {};
		}

		auto* castedElseCase = validateImplicitCast(thenCase->type(), *elseCase, context);

		if (castedElseCase)
			return new ConditionalExpressionIr(*condition, *thenCase, *castedElseCase);

		auto *castedThenCase = validateImplicitCast(elseCase->type(), *thenCase, context);

		if (castedThenCase)
			return new ConditionalExpressionIr(*condition, *castedThenCase, *elseCase);

		log::incompatibleConditionalTypes(ast.snippet());
		return {};
	}

	IdentifierExpressionIr* validateIdentifierExpression(const IdentifierExpressionAst& ast, LocalContext& context)
	{
		auto *result = context.resolveSymbol(ast.identifier());

		if (!result)
		{
			log::undefinedEntityError(ast.identifier());
			return {};
		}

		return new IdentifierExpressionIr(*result);
	}

	ExpressionIr* validateCastExpression(const CastExpressionAst& ast, LocalContext& context)
	{
		auto* expression = validateExpression(ast.expression(), context);
		auto* toType = validateTypeAnnotation(ast.typeAnnotation(), context);

		if (!expression || !toType)
			return {};

		const auto& expressionType = expression->type();

		if (*toType == expressionType)
			return expression;

		auto& typeContext = context.globalContext().getTypeContext(expressionType);
		auto* cast = typeContext.getExplicitCastTo(*toType);

		if (!cast)
		{
			log::invalidExplicitCastError(ast.snippet(), expression->type(), *toType);
			return {};
		}

		return new CastExpressionIr(*expression, *cast);
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
				log::invalidIntegerLiteralError(snippet);
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
		auto *context = new StringLiteralIr(String(ast.text()));

		return context;
	}

	CharLiteralIr* validateCharLiteral(const CharLiteralAst& ast)
	{
		// TODO: Allow for integer literals from long char literals;

		const auto& snippet = ast.snippet();

		if (snippet.length() != 3)
		{
			log::invalidCharLiteralError(snippet);
			return {};
		}

		auto value = snippet[1];

		return new CharLiteralIr(value);
	}

	BoolLiteralIr* validateBoolLiteral(const BoolLiteralAst& ast)
	{
		return new BoolLiteralIr(ast.value());
	}
}
