#ifndef PARKA_VALIDATOR_VALIDATOR_HPP
#define PARKA_VALIDATOR_VALIDATOR_HPP

#include "parka/ast/Ast.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ast/Prototype.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/ir/Ir.hpp"
#include "parka/ir/Prototype.hpp"
#include "parka/ir/ValueType.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/util/Optional.hpp"

namespace parka::validator
{
	// TODO: Consider making this a class that will store errors/state
	Optional<ir::Ir> validate(const ast::Ast& ast);
	Optional<ir::Ir> validate(PackageSymbolTable& package);
	ir::FunctionIr *validate(FunctionSymbolTable& function);
	Optional<ir::PrototypeIr> validate(const ast::PrototypeAst& prototype, SymbolTable& symbolTable);
	Optional<ir::ValueType> validate(const ast::TypeAnnotationAst& ast, SymbolTable& symbolTable);
	ir::ParameterIr *validate(const ast::ParameterAst& ast, SymbolTable& symbolTable);
	ir::ExpressionIr *validate(const ast::ExpressionAst& expression, SymbolTable& symbolTable);
}

#endif
