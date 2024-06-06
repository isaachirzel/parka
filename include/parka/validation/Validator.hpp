#ifndef PARKA_VALIDATION_VALIDATOR_HPP
#define PARKA_VALIDATION_VALIDATOR_HPP

#include "parka/ast/AssignmentStatementAst.hpp"
#include "parka/ast/Ast.hpp"
#include "parka/ast/BinaryExpressionAst.hpp"
#include "parka/ast/BlockStatementAst.hpp"
#include "parka/ast/BoolLiteralAst.hpp"
#include "parka/ast/BreakStatementAst.hpp"
#include "parka/ast/CallExpressionAst.hpp"
#include "parka/ast/CastExpressionAst.hpp"
#include "parka/ast/CharLiteralAst.hpp"
#include "parka/ast/ConditionalExpressionAst.hpp"
#include "parka/ast/ContinueStatementAst.hpp"
#include "parka/ast/DeclarationStatementAst.hpp"
#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/ExpressionStatementAst.hpp"
#include "parka/ast/FloatLiteralAst.hpp"
#include "parka/ast/ForStatementAst.hpp"
#include "parka/ast/FunctionBodyAst.hpp"
#include "parka/ast/IdentifierExpressionAst.hpp"
#include "parka/ast/IfStatementAst.hpp"
#include "parka/ast/PrototypeAst.hpp"
#include "parka/ast/ReturnStatementAst.hpp"
#include "parka/ast/TypeAnnotationAst.hpp"
#include "parka/ast/IntegerLiteralAst.hpp"
#include "parka/ast/StringLiteralAst.hpp"
#include "parka/ast/YieldStatementAst.hpp"
#include "parka/ir/AssignmentStatementIr.hpp"
#include "parka/ir/BinaryExpressionIr.hpp"
#include "parka/ir/BlockStatementIr.hpp"
#include "parka/ir/BoolLiteralIr.hpp"
#include "parka/ir/BreakStatementIr.hpp"
#include "parka/ir/CallExpressionIr.hpp"
#include "parka/ir/CallOperatorIr.hpp"
#include "parka/ir/CharLiteralIr.hpp"
#include "parka/ir/ConditionalExpressionIr.hpp"
#include "parka/ir/ContinueStatementIr.hpp"
#include "parka/ir/DeclarationStatementIr.hpp"
#include "parka/ir/ExpressionStatementIr.hpp"
#include "parka/ir/FloatLiteralIr.hpp"
#include "parka/ir/ForStatementIr.hpp"
#include "parka/ir/FunctionBodyIr.hpp"
#include "parka/ir/IdentifierExpressionIr.hpp"
#include "parka/ir/IfStatementIr.hpp"
#include "parka/ir/Ir.hpp"
#include "parka/ir/PrototypeIr.hpp"
#include "parka/ir/ReturnStatementIr.hpp"
#include "parka/ir/StatementIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/IntegerLiteralIr.hpp"
#include "parka/ir/StringLiteralIr.hpp"
#include "parka/ir/YieldStatementIr.hpp"
#include "parka/validation/FunctionContext.hpp"
#include "parka/validation/LocalContext.hpp"
#include "parka/util/Result.hpp"

namespace parka::validation
{
	Result<ir::Ir> validateAst(const ast::Ast& ast);
	ir::FunctionIr* validateFunction(const ast::FunctionAst& ast, FunctionContext& context);
	Result<ir::PrototypeIr> validatePrototype(const ast::PrototypeAst& prototype, FunctionContext& context);
	ir::ParameterIr* validateParameter(const ast::ParameterAst& ast, FunctionContext& context);
	Result<ir::FunctionBodyIr> validateFunctionBody(const ast::FunctionBodyAst& ast, FunctionContext& context);
	ir::VariableIr* validateVariable(const ast::VariableAst& ast, LocalContext& context);
	const ir::TypeIr* validateTypeAnnotation(const ast::TypeAnnotationAst& ast, Context& context);
	ir::StatementIr* validateStatement(const ast::StatementAst& statement, LocalContext& context);
	ir::DeclarationStatementIr* validateDeclarationStatement(const ast::DeclarationStatementAst& ast, LocalContext& context);
	ir::ExpressionStatementIr* validateExpressionStatement(const ast::ExpressionStatementAst& ast, LocalContext& context);
	ir::AssignmentStatementIr* validateAssignmentStatement(const ast::AssignmentStatementAst& ast, LocalContext& context);
	ir::ReturnStatementIr* validateReturnStatement(const ast::ReturnStatementAst& ast, LocalContext& context);
	ir::BreakStatementIr* validateBreakStatement(const ast::BreakStatementAst& ast, LocalContext& context);
	ir::ContinueStatementIr* validateContinueStatement(const ast::ContinueStatementAst& ast, LocalContext& context);
	ir::YieldStatementIr* validateYieldStatement(const ast::YieldStatementAst& ast, LocalContext& context);
	ir::ForStatementIr* validateForStatement(const ast::ForStatementAst& ast, LocalContext& context);
	ir::BlockStatementIr* validateBlockStatement(const ast::BlockStatementAst& ast, LocalContext& context);
	ir::IfStatementIr* validateIfStatement(const ast::IfStatementAst& ast, LocalContext& context);
	ir::ExpressionIr* validateExpression(const ast::ExpressionAst& expression, LocalContext& context);
	ir::BinaryExpressionIr* validateBinaryExpression(const ast::BinaryExpressionAst& ast, LocalContext& context);
	ir::CallExpressionIr* validateCallExpression(const ast::CallExpressionAst& ast, LocalContext& context);
	ir::ConditionalExpressionIr* validateConditionalExpression(const ast::ConditionalExpressionAst& ast, LocalContext& context);
	ir::IdentifierExpressionIr* validateIdentifierExpression(const ast::IdentifierExpressionAst& ast, LocalContext& context);
	ir::ExpressionIr* validateCastExpression(const ast::CastExpressionAst& ast, LocalContext& context);
	ir::IntegerLiteralIr* validateIntegerLiteral(const ast::IntegerLiteralAst& ast);
	ir::FloatLiteralIr* validateFloatLiteral(const ast::FloatLiteralAst& ast);
	ir::StringLiteralIr* validateStringLiteral(const ast::StringLiteralAst& ast);
	ir::CharLiteralIr* validateCharLiteral(const ast::CharLiteralAst& ast);
	ir::BoolLiteralIr* validateBoolLiteral(const ast::BoolLiteralAst& ast);
}

#endif
