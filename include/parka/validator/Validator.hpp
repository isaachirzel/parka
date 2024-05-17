#ifndef PARKA_VALIDATOR_VALIDATOR_HPP
#define PARKA_VALIDATOR_VALIDATOR_HPP

#include "parka/ast/AssignmentStatementAst.hpp"
#include "parka/ast/Ast.hpp"
#include "parka/ast/BinaryExpressionAst.hpp"
#include "parka/ast/BlockStatementAst.hpp"
#include "parka/ast/BoolLiteralAst.hpp"
#include "parka/ast/BreakStatementAst.hpp"
#include "parka/ast/CallExpressionAst.hpp"
#include "parka/ast/CharLiteralAst.hpp"
#include "parka/ast/ContinueStatementAst.hpp"
#include "parka/ast/DeclarationStatementAst.hpp"
#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/ExpressionStatementAst.hpp"
#include "parka/ast/FloatLiteralAst.hpp"
#include "parka/ast/ForStatementAst.hpp"
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
#include "parka/ir/CharLiteralIr.hpp"
#include "parka/ir/ContinueStatementIr.hpp"
#include "parka/ir/DeclarationStatementIr.hpp"
#include "parka/ir/ExpressionStatementIr.hpp"
#include "parka/ir/FloatLiteralIr.hpp"
#include "parka/ir/ForStatementIr.hpp"
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
#include "parka/symbol/SymbolTable.hpp"
#include "parka/util/Result.hpp"

namespace parka::validator
{
	// TODO: Consider making this a class that will store errors/state. Upon validating something that needs a symbol table, a new validator would be constructed
	Result<ir::Ir> validateAst(const ast::Ast& ast);
	ir::FunctionIr* validateFunction(const ast::FunctionAst& ast, FunctionSymbolTable& symbolTable);
	Result<ir::PrototypeIr> validatePrototype(const ast::PrototypeAst& prototype, FunctionSymbolTable& symbolTable);
	Result<ir::Type> validateTypeAnnotation(const ast::TypeAnnotationAst& ast, SymbolTable& symbolTable);
	ir::ParameterIr* validateParameter(const ast::ParameterAst& ast, FunctionSymbolTable& symbolTable);
	ir::ExpressionIr* validateExpression(const ast::ExpressionAst& expression, FunctionSymbolTable& symbolTable);
	ir::BinaryExpressionIr* validateBinaryExpression(const ast::BinaryExpressionAst& ast, FunctionSymbolTable& symbolTable);
	ir::CallExpressionIr* validateCallExpression(const ast::CallExpressionAst& ast, FunctionSymbolTable& symbolTable);
	ir::IdentifierExpressionIr* validateIdentifierExpression(const ast::IdentifierExpressionAst& ast, FunctionSymbolTable& symbolTable);
	ir::IntegerLiteralIr* validateIntegerLiteral(const ast::IntegerLiteralAst& ast);
	ir::FloatLiteralIr* validateFloatLiteral(const ast::FloatLiteralAst& ast);
	ir::StringLiteralIr* validateStringLiteral(const ast::StringLiteralAst& ast);
	ir::CharLiteralIr* validateCharLiteral(const ast::CharLiteralAst& ast);
	ir::BoolLiteralIr* validateBoolLiteral(const ast::BoolLiteralAst& ast);
	ir::StatementIr* validateStatement(const ast::StatementAst& statement, FunctionSymbolTable& symbolTable);
	ir::DeclarationStatementIr* validateDeclarationStatement(const ast::DeclarationStatementAst& ast, FunctionSymbolTable& symbolTable);
	ir::ExpressionStatementIr* validateExpressionStatement(const ast::ExpressionStatementAst& ast, FunctionSymbolTable& symbolTable);
	ir::AssignmentStatementIr* validateAssignmentStatement(const ast::AssignmentStatementAst& ast, FunctionSymbolTable& symbolTable);
	ir::ReturnStatementIr* validateReturnStatement(const ast::ReturnStatementAst& ast, FunctionSymbolTable& symbolTable);
	ir::BreakStatementIr* validateBreakStatement(const ast::BreakStatementAst& ast, FunctionSymbolTable& symbolTable);
	ir::ContinueStatementIr* validateContinueStatement(const ast::ContinueStatementAst& ast, FunctionSymbolTable& symbolTable);
	ir::YieldStatementIr* validateYieldStatement(const ast::YieldStatementAst& ast, FunctionSymbolTable& symbolTable);
	ir::ForStatementIr* validateForStatement(const ast::ForStatementAst& ast, FunctionSymbolTable& symbolTable);
	ir::BlockStatementIr* validateBlockStatement(const ast::BlockStatementAst& ast, FunctionSymbolTable& symbolTable);
	ir::IfStatementIr* validateIfStatement(const ast::IfStatementAst& ast, FunctionSymbolTable& symbolTable);
	ir::VariableIr* validateVariable(const ast::VariableAst& ast, ir::ExpressionIr *value, FunctionSymbolTable& symbolTable);
}

#endif
