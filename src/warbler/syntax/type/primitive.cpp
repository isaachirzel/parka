#include <warbler/syntax//type/primitive.hpp>

#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Primitive::Primitive(Identifier&& name, u32 bytes, PrimitiveType type) :
	_name(std::move(name)),
	_bytes(bytes),
	_type(type)
	{}

	bool Primitive::validate(semantics::ModuleContext& mod_ctx)
	{
		print_note("Primitive::validate is not defined");
		return true;
	}

	void Primitive::print_tree(u32 depth) const
	{
		switch (_type)
		{
			case PRIMITIVE_INTEGER:
				std::cout << tree_branch(depth) << "i" << _bytes * 8 << '\n';
				break;

			case PRIMITIVE_UNSIGNED:
				std::cout << tree_branch(depth) << "u" << _bytes * 8 << '\n';
				break;

			case PRIMITIVE_BINARY:
				std::cout << tree_branch(depth) << "b" << _bytes * 8 << '\n';
				break;

			case PRIMITIVE_FLOAT:
				std::cout << tree_branch(depth) << "f" << _bytes * 8 << '\n';
				break;

			case PRIMITIVE_BOOL:
				std::cout << tree_branch(depth) << "bool\n";
				break;

			case PRIMITIVE_CHAR:
				std::cout << tree_branch(depth) << "char\n";
				break;

			case PRIMITIVE_STR:
				std::cout << tree_branch(depth) << "str\n";
				break;
		}
	}
}