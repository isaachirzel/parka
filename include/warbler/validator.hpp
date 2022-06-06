#ifndef WARBLER_VALIDATOR_HPP
#define WARBLER_VALIDATOR_HPP

#include <warbler/syntax.hpp>
#include <warbler/context.hpp>
#include <warbler/symbol_table.hpp>

namespace warbler
{
	Result<ParameterContext> validate_parameter(const ParameterSyntax& syntax, GlobalSymbolTable& globals, LocalSymbolTable& locals);
	Result<VariableContext> validate_variable(const VariableSyntax& syntax);
	bool validate_struct(const StructSyntax& syntax, GlobalSymbolTable& symbols, Array<String>& containing_types);
	Result<PackageContext> validate_module(const ModuleSyntax& syntax);
	Result<ProgramContext> validate(const ProgramSyntax& syntax);
}

#endif
