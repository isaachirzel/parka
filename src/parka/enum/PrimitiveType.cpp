#include "parka/enum/PrimitiveType.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const PrimitiveType& primitiveType)
	{
		switch (primitiveType)
		{
			case PrimitiveType::Void:
				out << "void";
				break;
				
			case PrimitiveType::Integer:
				out << "integer";
				break;
				
			case PrimitiveType::U8:
				out << "u8";
				break;
				
			case PrimitiveType::U16:
				out << "u16";
				break;
				
			case PrimitiveType::U32:
				out << "u32";
				break;
				
			case PrimitiveType::U64:
				out << "u64";
				break;
				
			case PrimitiveType::I8:
				out << "i8";
				break;
				
			case PrimitiveType::I16:
				out << "i16";
				break;
				
			case PrimitiveType::I32:
				out << "i32";
				break;
				
			case PrimitiveType::I64:
				out << "i64";
				break;
				
			case PrimitiveType::Float:
				out << "float";
				break;
				
			case PrimitiveType::F32:
				out << "f32";
				break;
				
			case PrimitiveType::F64:
				out << "f64";
				break;
				
			case PrimitiveType::Bool:
				out << "bool";
				break;
				
			case PrimitiveType::Char:
				out << "char";
				break;
				
			case PrimitiveType::String:
				out << "string";
				break;
		}

		return out;
	}
}
