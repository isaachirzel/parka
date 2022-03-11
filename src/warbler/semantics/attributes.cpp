#include <warbler/semantics/attributes.hpp>

#include <warbler/syntax/function/function_signature.hpp>
#include <warbler/syntax/function/parameter.hpp>
#include <warbler/syntax/statement/declaration.hpp>
#include <cassert>

namespace warbler::semantics
{
	VariableContext::VariableContext(Optional<Type>&& type, VariableState state) :
	type(std::move(type)),
	state(state)
	{}

	ParameterContext::ParameterContext(Type&& type, ParameterState state) :
	type(std::move(type)),
	state(ParameterState::Valid)
	{}

	FunctionContext::FunctionContext(Array<ParameterContext>&& parameters, Type&& return_type) :
	parameter(std::move(parameters)),
	return_type(std::move(return_type))
	{}

	Context::Context(VariableContext&& variable) :
	_variable(std::move(declaration)),
	_type(SymbolType::Variable)
	{}

	Context::Context(FunctionContext&& function) :
	_function(std::move(function)),
	_type(SymbolType::Function)
	{}

	Context::Context(ParameterContext&& parameter) :
	_parameter(std::move(parameter)),
	_type(SymbolType::Parameter)
	{}

	Context::Context(Context&& other)
	{
		switch (_type)
		{
			case SymbolType::Function:
				new (&_function) auto(std::move(other._function));
				break;

			case SymbolType::Parameter:
				new (&_parameter) auto(std::move(other._parameter));
				break;
				
			case SybmolType::Variable:
				new (&_variable) auto(std::move(other._variable));
				break;
		}
	}

	Context::~Context()
	{
		switch (_type)
		{
			case SymbolType::Function:
				_function.~FunctionContext();
				break;

			case SymbolType::Parameter:
				_parameter.~ParameterContext();
				break;

			case SybmolType::Variable:
				_variable.~VariableContext();
				break;
		}
	}
}
