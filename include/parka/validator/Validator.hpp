#ifndef PARKA_VALIDATOR_VALIDATOR_HPP
#define PARKA_VALIDATOR_VALIDATOR_HPP

#include "parka/ast/Ast.hpp"
#include "parka/ast/BinaryExpression.hpp"
#include "parka/ast/BlockExpression.hpp"
#include "parka/ast/DeclarationStatement.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ast/IdentifierExpression.hpp"
#include "parka/ast/Prototype.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/ast/IntegerLiteral.hpp"
#include "parka/ast/StringLiteral.hpp"
#include "parka/ir/BinaryExpression.hpp"
#include "parka/ir/BlockExpression.hpp"
#include "parka/ir/DeclarationStatement.hpp"
#include "parka/ir/IdentifierExpression.hpp"
#include "parka/ir/Ir.hpp"
#include "parka/ir/Prototype.hpp"
#include "parka/ir/Type.hpp"
#include "parka/ir/IntegerLiteral.hpp"
#include "parka/ir/StringLiteral.hpp"
#include "parka/symbol/LocalSymbolTable.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/util/Optional.hpp"

namespace parka::validator
{
	// TODO: Consider making this a class that will store errors/state. Upon validating something that needs a symbol table, a new validator would be constructed
	Optional<ir::Ir> validateAst(const ast::Ast& ast);
	Optional<ir::Ir> validatePackage(PackageSymbolTable& symbolTable);
	ir::FunctionIr *validateFunction(const ast::FunctionAst& ast, SymbolTable& parentSymbolTable);
	Optional<ir::PrototypeIr> validatePrototype(const ast::PrototypeAst& prototype, LocalSymbolTable& symbolTable);
	Optional<ir::Type> validateTypeAnnotation(const ast::TypeAnnotationAst& ast, SymbolTable& symbolTable);
	ir::ParameterIr *validateParameter(const ast::ParameterAst& ast, LocalSymbolTable& symbolTable);
	ir::ExpressionIr *validateExpression(const ast::ExpressionAst& expression, LocalSymbolTable& symbolTable);
	ir::BlockExpressionIr *validateBlockExpression(const ast::BlockExpressionAst& ast, LocalSymbolTable& symbolTable);
	ir::BinaryExpressionIr *validateBinaryExpression(const ast::BinaryExpressionAst& ast, LocalSymbolTable& symbolTable);
	ir::IdentifierExpressionIr *validateIdentifierExpression(const ast::IdentifierExpressionAst& ast, LocalSymbolTable& symbolTable);
	ir::IntegerLiteralIr *validateIntegerLiteral(const ast::IntegerLiteralAst& ast);
	ir::StringLiteralIr *validateStringLiteral(const ast::StringLiteralAst& ast);
	ir::StatementIr *validateStatement(const ast::StatementAst& statement, LocalSymbolTable& symbolTable);
	ir::StatementIr *validateDeclarationStatement(const ast::DeclarationStatementAst& ast, LocalSymbolTable& symbolTable);
	ir::VariableIr *validateVariable(const ast::VariableAst& ast, ir::ExpressionIr *value, LocalSymbolTable& symbolTable);
}

#endif
