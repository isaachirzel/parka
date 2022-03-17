#include <warbler/context.hpp>

namespace warbler
{
	ConstantContext::ConstantContext(char character) :
	_character(character),
	_type(ConstantType::Character)
	{}

	ConstantContext::ConstantContext(String&& string) :
	_string(std::move(string)),
	_type(ConstantType::String)
	{}

	ConstantContext::ConstantContext(u64 integer) :
	_integer(integer),
	_type(ConstantType::Integer)
	{}

	ConstantContext::ConstantContext(double floating) :
	_floating(floating),
	_type(ConstantType::Float)
	{}

	ConstantContext::ConstantContext(bool boolean) :
	_boolean(boolean),
	_type(ConstantType::Boolean)
	{}

	ConstantContext::ConstantContext(ConstantContext&& other) :
	_type(other._type)
	{
		switch (_type)
		{
			case ConstantType::Character:
				_character = other._character;
				break;

			case ConstantType::String:
				new (&_string) auto(std::move(other._string));
				break;

			case ConstantType::Integer:
				_integer = other._integer;
				break;

			case ConstantType::Float:
				_floating = other._floating;
				break;

			case ConstantType::Boolean:
				_boolean = other._boolean;
				break;
		}
	}

	ConstantContext::~ConstantContext()
	{
		if (_type == ConstantType::String)
			_string.~basic_string();
	}

	ExpressionContext::ExpressionContext(ConstantContext&& constant) :
	_constant(new ConstantContext(std::move(constant))),
	_type(ExpressionType::Constant)
	{}

	ExpressionContext::ExpressionContext(ExpressionContext&& other) :
	_type(ExpressionType::Constant)
	{
		switch (_type)
		{
			case ExpressionType::Constant:
				_constant = other._constant;
				other._constant = nullptr;
				break;

			default:
				break;
		}
	}

	TypeDefinitionContext::TypeDefinitionContext(String&& symbol, StructContext&& struct_def) :
	_symbol(std::move(symbol)),
	_struct_def(std::move(struct_def)),
	_type(TypeDefinitionType::Struct)
	{}

	TypeDefinitionContext::TypeDefinitionContext(TypeDefinitionContext&& other) :
	_symbol(std::move(other._symbol)),
	_type(other._type)
	{
		switch (_type)
		{
			case TypeDefinitionType::Struct:
				new (&_struct_def) auto(std::move(other._struct_def));
				break;
		}
	}

	TypeDefinitionContext::~TypeDefinitionContext()
	{
		switch (_type)
		{
			case TypeDefinitionType::Struct:
				_struct_def.~StructContext();
				break;
		}
	}

	SymbolContext::SymbolContext(VariableContext& variable) :
	_variable(&variable),
	_type(SymbolType::Variable)
	{}

	SymbolContext::SymbolContext(FunctionContext& function) :
	_type(SymbolType::Function)
	{}

	SymbolContext::SymbolContext(ParameterContext& parameter) :
	_type(SymbolType::Parameter)
	{}

	SymbolContext::SymbolContext(TypeDefinitionContext& definition) :
	_type(SymbolType::TypeDefinition)
	{}

	SymbolContext::SymbolContext(const SymbolContext& other) :
	_type(other._type)
	{
		switch (_type)
		{
			case SymbolType::Variable:
				_variable = other._variable;
				break;
				
			case SymbolType::Function:
				_function = other._function;
				break;

			case SymbolType::Parameter:
				_parameter = other._parameter;
				break;

			case SymbolType::TypeDefinition:
				_definition = other._definition;
				break;
		}
	}
}
