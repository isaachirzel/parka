#ifndef PARKA_VALIDATOR_VALIDATOR_HPP
#define PARKA_VALIDATOR_VALIDATOR_HPP

#include "parka/ast/Ast.hpp"
#include "parka/ast/BinaryExpressionAst.hpp"
#include "parka/ast/BlockExpressionAst.hpp"
#include "parka/ast/BoolLiteralAst.hpp"
#include "parka/ast/BreakStatementAst.hpp"
#include "parka/ast/CharLiteralAst.hpp"
#include "parka/ast/ContinueStatementAst.hpp"
#include "parka/ast/DeclarationStatementAst.hpp"
#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/FloatLiteralAst.hpp"
#include "parka/ast/ForStatementAst.hpp"
#include "parka/ast/IdentifierExpressionAst.hpp"
#include "parka/ast/PrototypeAst.hpp"
#include "parka/ast/ReturnStatementAst.hpp"
#include "parka/ast/TypeAnnotationAst.hpp"
#include "parka/ast/IntegerLiteralAst.hpp"
#include "parka/ast/StringLiteralAst.hpp"
#include "parka/ast/YieldStatementAst.hpp"
#include "parka/ir/BinaryExpressionIr.hpp"
#include "parka/ir/BlockExpressionIr.hpp"
#include "parka/ir/BoolLiteralIr.hpp"
#include "parka/ir/CharLiteralIr.hpp"
#include "parka/ir/FloatLiteralIr.hpp"
#include "parka/ir/IdentifierExpressionIr.hpp"
#include "parka/ir/Ir.hpp"
#include "parka/ir/PrototypeIr.hpp"
#include "parka/ir/StatementIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/IntegerLiteralIr.hpp"
#include "parka/ir/StringLiteralIr.hpp"
#include "parka/symbol/LocalSymbolTable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/util/Result.hpp"

namespace parka::validator
{
	// TODO: Consider making this a class that will store errors/state. Upon validating something that needs a symbol table, a new validator would be constructed
	Result<ir::Ir> validateAst(const ast::Ast& ast);
	ir::FunctionIr *validateFunction(const ast::FunctionAst& ast, SymbolTable& parentSymbolTable);
	Result<ir::PrototypeIr> validatePrototype(const ast::PrototypeAst& prototype, LocalSymbolTable& symbolTable);
	Result<ir::Type> validateTypeAnnotation(const ast::TypeAnnotationAst& ast, SymbolTable& symbolTable);
	ir::ParameterIr *validateParameter(const ast::ParameterAst& ast, LocalSymbolTable& symbolTable);
	ir::ExpressionIr *validateExpression(const ast::ExpressionAst& expression, LocalSymbolTable& symbolTable);
	ir::BlockExpressionIr *validateBlockExpression(const ast::BlockExpressionAst& ast, LocalSymbolTable& symbolTable);
	ir::BinaryExpressionIr *validateBinaryExpression(const ast::BinaryExpressionAst& ast, LocalSymbolTable& symbolTable);
	ir::IdentifierExpressionIr *validateIdentifierExpression(const ast::IdentifierExpressionAst& ast, LocalSymbolTable& symbolTable);
	ir::IntegerLiteralIr *validateIntegerLiteral(const ast::IntegerLiteralAst& ast);
	ir::FloatLiteralIr *validateFloatLiteral(const ast::FloatLiteralAst& ast);
	ir::StringLiteralIr *validateStringLiteral(const ast::StringLiteralAst& ast);
	ir::CharLiteralIr *validateCharLiteral(const ast::CharLiteralAst& ast);
	ir::BoolLiteralIr *validateBoolLiteral(const ast::BoolLiteralAst& ast);
	ir::StatementIr *validateStatement(const ast::StatementAst& statement, LocalSymbolTable& symbolTable);
	ir::StatementIr *validateDeclarationStatement(const ast::DeclarationStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::StatementIr *validateReturnStatement(const ast::ReturnStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::StatementIr *validateBreakStatement(const ast::BreakStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::StatementIr *validateContinueStatement(const ast::ContinueStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::StatementIr *validateYieldStatement(const ast::YieldStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::StatementIr *validateForStatement(const ast::ForStatementAst& ast, LocalSymbolTable& symbolTable);
	// Result<ir::RangeIr> validateForStatement(const ast::ForStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::VariableIr *validateVariable(const ast::VariableAst& ast, ir::ExpressionIr *value, LocalSymbolTable& symbolTable);
}

#endif
