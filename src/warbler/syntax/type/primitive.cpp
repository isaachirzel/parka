#include <warbler/syntax/type/primitive.hpp>

#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Primitive::Primitive(Identifier&& name, u32 bytes, PrimitiveType type) :
	_name(std::move(name)),
	_bytes(bytes),
	_type(type)
	{}

	// 	switch (_type)
	// 	{
	// 		case PrimitiveType::Integer:

	// 			print_branch(depth) << "i" << _bytes * 8 << '\n';
	// 			break;

	// 		case PrimitiveType::Unsigned:
	// 			print_branch(depth) << "u" << _bytes * 8 << '\n';
	// 			break;

	// 		case PrimitiveType::Binary:
	// 			print_branch(depth) << "b" << _bytes * 8 << '\n';
	// 			break;

	// 		case PrimitiveType::Float:
	// 			print_branch(depth) << "f" << _bytes * 8 << '\n';
	// 			break;

	// 		case PrimitiveType::Bool:
	// 			print_branch(depth) << "bool\n";
	// 			break;

	// 		case PrimitiveType::Char:
	// 			print_branch(depth) << "char\n";
	// 			break;

	// 		case PrimitiveType::Str:
	// 			print_branch(depth) << "str\n";
	// 			break;
	// 	}
	// }
}