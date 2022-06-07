#include <warbler/context.hpp>

#include <stdexcept>

namespace warbler
{
	ConstantContext::ConstantContext(char character) :
	_character(character),
	_type(ConstantType::Character)
	{}

	ConstantContext::ConstantContext(const String& string) :
	_string(string),
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

	StatementContext::StatementContext(BlockStatementContext&& block) :
	_block(std::move(block)),
	_type(StatementType::Block)
	{}

	StatementContext::StatementContext(DeclarationContext&& variable) :
	_declaration(std::move(variable)),
	_type(StatementType::Declaration)
	{}

	StatementContext::StatementContext(StatementContext&& other) :
	_type(other._type)
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
				throw std::runtime_error("Construction of statement context does not yet support this type of statement");
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
				throw std::runtime_error("Statement destruction does not yet support this type of statement");
		}
	}
}
