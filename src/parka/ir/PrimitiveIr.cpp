#include "parka/ir/PrimitiveIr.hpp"
#include "parka/enum/EntityType.hpp"

namespace parka::ir
{
	constexpr const char* getPrimitiveTypeSymbol(PrimitiveType primitiveType)
	{
		switch (primitiveType)
		{
			case PrimitiveType::Void:
				return "void";

			case PrimitiveType::Integer:
				return "integer";

			case PrimitiveType::U8:
				return "u8";

			case PrimitiveType::U16:
				return "u16";

			case PrimitiveType::U32:
				return "u32";

			case PrimitiveType::U64:
				return "u64";

			case PrimitiveType::I8:
				return "i8";

			case PrimitiveType::I16:
				return "i16";

			case PrimitiveType::I32:
				return "i32";

			case PrimitiveType::I64:
				return "i64";

			case PrimitiveType::Float:
				return "float";

			case PrimitiveType::F32:
				return "f32";

			case PrimitiveType::F64:
				return "f64";

			case PrimitiveType::Bool:
				return "bool";

			case PrimitiveType::Char:
				return "char";

			case PrimitiveType::String:
				return "string";
		}

		return "invalid";
	}

	PrimitiveIr PrimitiveIr::voidPrimitive(PrimitiveType::Void);
	PrimitiveIr PrimitiveIr::integerPrimitive(PrimitiveType::Integer);
	PrimitiveIr PrimitiveIr::u8Primitive(PrimitiveType::U8);
	PrimitiveIr PrimitiveIr::u16Primitive(PrimitiveType::U16);
	PrimitiveIr PrimitiveIr::u32Primitive(PrimitiveType::U32);
	PrimitiveIr PrimitiveIr::u64Primitive(PrimitiveType::U64);
	PrimitiveIr PrimitiveIr::i8Primitive(PrimitiveType::I8);
	PrimitiveIr PrimitiveIr::i16Primitive(PrimitiveType::I16);
	PrimitiveIr PrimitiveIr::i32Primitive(PrimitiveType::I32);
	PrimitiveIr PrimitiveIr::i64Primitive(PrimitiveType::I64);
	PrimitiveIr PrimitiveIr::floatPrimitive(PrimitiveType::Float);
	PrimitiveIr PrimitiveIr::f32Primitive(PrimitiveType::F32);
	PrimitiveIr PrimitiveIr::f64Primitive(PrimitiveType::F64);
	PrimitiveIr PrimitiveIr::boolPrimitive(PrimitiveType::Bool);
	PrimitiveIr PrimitiveIr::charPrimitive(PrimitiveType::Char);
	PrimitiveIr PrimitiveIr::stringPrimitive(PrimitiveType::String);

	PrimitiveIr::PrimitiveIr(PrimitiveType primitiveType):
		EntityIr(EntityType::Primitive),
		TypeIr(TypeCategory::Primitive),
		_symbol(getPrimitiveTypeSymbol(primitiveType)),
		_primitiveType(primitiveType)
	{}

	std::ostream& PrimitiveIr::printType(std::ostream& out) const
	{
		out << _symbol;

		return out;
	}

	std::ostream& operator<<(std::ostream& out, const PrimitiveIr& primitive)
	{
		out << primitive._symbol;

		return out;
	}
}
