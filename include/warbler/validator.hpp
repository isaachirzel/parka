#ifndef WARBLER_VALIDATOR_HPP
#define WARBLER_VALIDATOR_HPP

#include <warbler/syntax.hpp>
#include <warbler/context.hpp>

namespace warbler
{
	Result<ParameterContext> validate_parameter(const ParameterSyntax& syntax);
	Result<VariableContext> validate_variable(const VariableSyntax& syntax);
	Result<ModuleContext> validate_module(const ModuleSyntax& syntax);
	Result<AstContext> validate(const AstSyntax& syntax);
}

#endif
