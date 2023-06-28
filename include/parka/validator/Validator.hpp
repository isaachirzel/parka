#ifndef PARKA_VALIDATOR_VALIDATOR_HPP
#define PARKA_VALIDATOR_VALIDATOR_HPP

#include "parka/ast/Ast.hpp"
#include "parka/ast/BinaryExpression.hpp"
#include "parka/ast/BlockExpression.hpp"
#include "parka/ast/DeclarationStatement.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ast/Prototype.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/ir/BinaryExpression.hpp"
#include "parka/ir/BlockExpression.hpp"
#include "parka/ir/DeclarationStatement.hpp"
#include "parka/ir/Ir.hpp"
#include "parka/ir/Prototype.hpp"
#include "parka/ir/ValueType.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/util/Optional.hpp"

namespace parka::validator
{
	// TODO: Consider making this a class that will store errors/state. Upon validating something that needs a symbol table, a new validator would be constructed
	Optional<ir::Ir> validateAst(const ast::Ast& ast);
	Optional<ir::Ir> validatePackage(PackageSymbolTable& package);
	ir::FunctionIr *validateFunction(FunctionSymbolTable& function);
	Optional<ir::PrototypeIr> validatePrototype(const ast::PrototypeAst& prototype, SymbolTable& symbolTable);
	Optional<ir::ValueType> validateTypeAnnotation(const ast::TypeAnnotationAst& ast, SymbolTable& symbolTable);
	ir::ParameterIr *validateParameter(const ast::ParameterAst& ast, SymbolTable& symbolTable);
	ir::ExpressionIr *validateExpression(const ast::ExpressionAst& expression, SymbolTable& symbolTable);
	ir::BlockExpressionIr *validateBlockExpression(const ast::BlockExpressionAst& ast, SymbolTable& symbolTable);
	ir::BinaryExpressionIr *validateBinaryExpression(const ast::BinaryExpressionAst& ast, SymbolTable& symbolTable);
	ir::StatementIr *validateStatement(const ast::StatementAst& statement, SymbolTable& symbolTable);
	ir::StatementIr *validateDeclarationStatement(const ast::DeclarationStatementAst& ast, SymbolTable& symbolTable);
	ir::VariableIr *validateVariable(const ast::VariableAst& ast, ir::ExpressionIr *value, SymbolTable& symbolTable);


}

#endif
