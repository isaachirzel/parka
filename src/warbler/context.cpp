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

	StatementContext::StatementContext(BlockStatementContext&& block) :
	_block(std::move(block)),
	_type(StatementType::Block)
	{}

	StatementContext::StatementContext(DeclarationContext&& variable) :
	_declaration(std::move(variable)),
	_type(StatementType::Declaration)
	{}

	StatementContext::StatementContext(StatementContext&& other) :
	_type()
	{
		switch (_type)
		{
			case StatementType::Block:
				new (&_block) auto(std::move(other._block));
				break;

			case StatementType::Declaration:
				new (&_declaration) auto(std::move(other._block));
				break;

			default:
				assert(false && "invalid statement type");
				break;
		}
	}

	StatementContext::~StatementContext()
	{
		switch (_type)
		{
			case StatementType::Block:
				_block.~Box();
				break;

			case StatementType::Declaration:
				_declaration.~Box();
				break;

			default:
				assert(false && "invalid statement type");
				break;
		}
	}
}
