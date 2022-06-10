#include <warbler/context.hpp>

#include <stdexcept>

namespace warbler
{
	PrimitiveContext primitives[] =
	{
		PrimitiveContext(PrimitiveType::UnsignedInteger, 0),
		PrimitiveContext(PrimitiveType::UnsignedInteger, 1),
		PrimitiveContext(PrimitiveType::UnsignedInteger, 2),
		PrimitiveContext(PrimitiveType::UnsignedInteger, 4),
		PrimitiveContext(PrimitiveType::UnsignedInteger, 8),
		PrimitiveContext(PrimitiveType::SignedInteger, 0),
		PrimitiveContext(PrimitiveType::SignedInteger, 1),
		PrimitiveContext(PrimitiveType::SignedInteger, 2),
		PrimitiveContext(PrimitiveType::SignedInteger, 4),
		PrimitiveContext(PrimitiveType::SignedInteger, 8),
		PrimitiveContext(PrimitiveType::FloatingPoint, 0),
		PrimitiveContext(PrimitiveType::FloatingPoint, 4),
		PrimitiveContext(PrimitiveType::FloatingPoint, 8),
		PrimitiveContext(PrimitiveType::Boolean, 1),
		PrimitiveContext(PrimitiveType::Character, 4)
	};

	const char *PrimitiveContext::type_name() const
	{
		switch (_type)
		{
			case PrimitiveType::SignedInteger:
				return "integer";
			case PrimitiveType::UnsignedInteger:
				return "unsigned integer";
			case PrimitiveType::FloatingPoint:
				return "float";
			case PrimitiveType::Boolean:
				return "boolean";
			case PrimitiveType::Character:
				return "character";
			case PrimitiveType::StringLiteral:
				return "string literal";

			default:
				break;
		}

		throw std::runtime_error("Invalid type");
	}

	usize primitive_count = sizeof(primitives) / sizeof(*primitives);

	ConstantContext::ConstantContext(char character) :
	_character(character),
	_type(ConstantType::Character)
	{}

	ConstantContext::ConstantContext(const String& string) :
	_string(string),
	_type(ConstantType::StringLiteral)
	{}

	ConstantContext::ConstantContext(i64 integer) :
	_integer(integer),
	_type(ConstantType::SignedInteger)
	{}

	ConstantContext::ConstantContext(u64 uinteger) :
	_uinteger(uinteger),
	_type(ConstantType::UnsignedInteger)
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

			case ConstantType::StringLiteral:
				new (&_string) auto(std::move(other._string));
				break;

			case ConstantType::SignedInteger:
				_integer = other._integer;
				break;

			case ConstantType::UnsignedInteger:
				_uinteger = other._uinteger;
				break;

			case ConstantType::Float:
				_floating = other._floating;
				break;

			case ConstantType::Boolean:
				_boolean = other._boolean;
				break;

			default:
				throw std::runtime_error("Invalid type");
		}
	}

	ConstantContext::~ConstantContext()
	{
		if (_type == ConstantType::StringLiteral)
			_string.~basic_string();
	}

	TypeAnnotationContext ConstantContext::type_annotation() const
	{
		switch (_type)
		{
			case ConstantType::Character:
				return CHAR_INDEX;

			case ConstantType::SignedInteger:
				return INT_LITERAL_INDEX;

			case ConstantType::UnsignedInteger:
				return UINT_LITERAL_INDEX;

			case ConstantType::Float:
				return FLOAT_LITERAL_INDEX;

			case ConstantType::Boolean:
				return BOOL_INDEX;

			default:
				throw std::runtime_error("context index is not implmeneted for this type");
		}
	}

	ExpressionContext::ExpressionContext(ConstantContext&& constant) :
	_constant(std::move(constant)),
	_type(ExpressionType::Constant)
	{}

	ExpressionContext::ExpressionContext(ExpressionContext&& other) :
	_type(ExpressionType::Constant)
	{
		switch (_type)
		{
			case ExpressionType::Constant:
				new (&_constant) auto(std::move(other._constant));
				break;

			default:
				throw std::runtime_error("Move construction is not implemented for this type");
		}
	}

	ExpressionContext::~ExpressionContext()
	{
		switch (_type)
		{
			case ExpressionType::Constant:
				_constant.~Box();
				break;

			default:
				break;
		}
	}

	TypeAnnotationContext ExpressionContext::type_annotation() const
	{
		switch (_type)
		{
			case ExpressionType::Constant:
				return _constant->type_annotation();

			default:
				break;
		}

		throw std::runtime_error("Type annotation is not implemented for this type");
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
				break;
		}
	}
}
