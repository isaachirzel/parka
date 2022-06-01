#ifndef WARBLER_VALIDATOR_HPP
#define WARBLER_VALIDATOR_HPP

#include <warbler/syntax.hpp>
#include <warbler/context.hpp>
#include <warbler/symbol_table.hpp>

namespace warbler
{
	Result<ParameterContext> validate_parameter(const ParameterSyntax& syntax);
	Result<VariableContext> validate_variable(const VariableSyntax& syntax);
	Result<TypeContext> validate_type_definition(const TypeSyntax& syntax, const SymbolTable& symbols);
	Result<PackageContext> validate_module(const ModuleSyntax& syntax);
	Result<ProgramContext> validate(const ProgramSyntax& syntax);
}

#endif
