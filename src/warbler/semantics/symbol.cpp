#include <warbler/semantics/symbol.hpp>
#include <cassert>

namespace warbler::semantics
{
	Symbol::Symbol(Variable&& variable) :
	_variable(std::move(variable)),
	_type(SymbolType::Variable)
	{}

	Symbol::Symbol(Function&& function) :
	_function(std::move(function)),
	_type(SymbolType::Function)
	{}

	Symbol::Symbol(Parameter& parameter) :
	_parameter(&parameter),
	_type(SymbolType::Parameter)
	{}

	Symbol::Symbol(Definition&& definition) :
	_definition(std::move(definition)),
	_type(SymbolType::TypeDefinition)
	{}
	
	Symbol::Symbol(Symbol&& other) :
	_type(other._type)
	{
		switch (_type)
		{
			case SymbolType::Function:
				new (&_function) auto(std::move(other._function));
				break;

			case SymbolType::Parameter:
				new (&_parameter) auto(std::move(other._parameter));
				break;
				
			case SymbolType::Variable:
				new (&_variable) auto(std::move(other._variable));
				break;

			case SymbolType::TypeDefinition:
				new (&_definition) auto(std::move(other._definition));
				break;
		}
	}

	Symbol& Symbol::operator=(Symbol&& other)
	{
		new (this) auto(std::move(other));
		return *this;
	}

	Symbol::~Symbol()
	{
		switch (_type)
		{
			case SymbolType::Function:
				_function.~Function();
				break;

			case SymbolType::Variable:
				_variable.~Variable();
				break;

			case SymbolType::TypeDefinition:
				_definition.~Definition();
				break;

			default:
				break;
		}
	}
}
