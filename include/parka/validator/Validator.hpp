#ifndef PARKA_VALIDATOR_VALIDATOR_HPP
#define PARKA_VALIDATOR_VALIDATOR_HPP

#include "parka/ast/AssignmentStatementAst.hpp"
#include "parka/ast/Ast.hpp"
#include "parka/ast/BinaryExpressionAst.hpp"
#include "parka/ast/BlockStatementAst.hpp"
#include "parka/ast/BoolLiteralAst.hpp"
#include "parka/ast/BreakStatementAst.hpp"
#include "parka/ast/CallExpressionAst.hpp"
#include "parka/ast/CastExpressionAst.hpp"
#include "parka/ast/CharLiteralAst.hpp"
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
#include "parka/ir/CastExpressionIr.hpp"
#include "parka/ir/CharLiteralIr.hpp"
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
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/LocalSymbolTable.hpp"
#include "parka/util/Result.hpp"

namespace parka::validator
{
	Result<ir::Ir> validateAst(const ast::Ast& ast);
	ir::FunctionIr* validateFunction(const ast::FunctionAst& ast, FunctionSymbolTable& symbolTable);
	Result<ir::PrototypeIr> validatePrototype(const ast::PrototypeAst& prototype, FunctionSymbolTable& symbolTable);
	ir::ParameterIr* validateParameter(const ast::ParameterAst& ast, FunctionSymbolTable& symbolTable);
	Result<ir::FunctionBodyIr> validateFunctionBody(const ast::FunctionBodyAst& ast, FunctionSymbolTable& symbolTable);
	ir::VariableIr* validateVariable(const ast::VariableAst& ast, LocalSymbolTable& symbolTable);
	Result<ir::TypeIr> validateTypeAnnotation(const ast::TypeAnnotationAst& ast, SymbolTable& symbolTable);
	ir::StatementIr* validateStatement(const ast::StatementAst& statement, LocalSymbolTable& symbolTable);
	ir::DeclarationStatementIr* validateDeclarationStatement(const ast::DeclarationStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::ExpressionStatementIr* validateExpressionStatement(const ast::ExpressionStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::AssignmentStatementIr* validateAssignmentStatement(const ast::AssignmentStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::ReturnStatementIr* validateReturnStatement(const ast::ReturnStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::BreakStatementIr* validateBreakStatement(const ast::BreakStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::ContinueStatementIr* validateContinueStatement(const ast::ContinueStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::YieldStatementIr* validateYieldStatement(const ast::YieldStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::ForStatementIr* validateForStatement(const ast::ForStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::BlockStatementIr* validateBlockStatement(const ast::BlockStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::IfStatementIr* validateIfStatement(const ast::IfStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::ExpressionIr* validateExpression(const ast::ExpressionAst& expression, LocalSymbolTable& symbolTable);
	ir::BinaryExpressionIr* validateBinaryExpression(const ast::BinaryExpressionAst& ast, LocalSymbolTable& symbolTable);
	ir::CallExpressionIr* validateCallExpression(const ast::CallExpressionAst& ast, LocalSymbolTable& symbolTable);
	ir::IdentifierExpressionIr* validateIdentifierExpression(const ast::IdentifierExpressionAst& ast, LocalSymbolTable& symbolTable);
	ir::CastExpressionIr* validateCastExpression(const ast::CastExpressionAst& ast, LocalSymbolTable& symbolTable);
	ir::IntegerLiteralIr* validateIntegerLiteral(const ast::IntegerLiteralAst& ast);
	ir::FloatLiteralIr* validateFloatLiteral(const ast::FloatLiteralAst& ast);
	ir::StringLiteralIr* validateStringLiteral(const ast::StringLiteralAst& ast);
	ir::CharLiteralIr* validateCharLiteral(const ast::CharLiteralAst& ast);
	ir::BoolLiteralIr* validateBoolLiteral(const ast::BoolLiteralAst& ast);
}

#endif
