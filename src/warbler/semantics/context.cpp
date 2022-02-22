#include <warbler/semantics/context.hpp>

#include <cassert>
#include <warbler/print.hpp>
#include <warbler/ast/type/primitive.hpp>
#include <warbler/ast/type/type_definition.hpp>

namespace warbler::semantics
{
	using ast::TypeDefinition;
	using ast::Primitive;
	using ast::Identifier;
	using ast::PrimitiveType;

	static Table<Ptr<TypeDefinition>> primitives;

	void init_context()
	{
		primitives.emplace("i8", Ptr<TypeDefinition> { new Primitive(Identifier("i8"), 1, ast::PRIMITIVE_INTEGER) });
		primitives.emplace("i16", Ptr<TypeDefinition> { new Primitive(Identifier("i16"), 2, ast::PRIMITIVE_INTEGER) });
		primitives.emplace("i32", Ptr<TypeDefinition> { new Primitive(Identifier("i32"), 2, ast::PRIMITIVE_INTEGER) });
		primitives.emplace("i64", Ptr<TypeDefinition> { new Primitive(Identifier("i64"), 2, ast::PRIMITIVE_INTEGER) });
	}

	ast::TypeDefinition *ModuleContext::get_type(const String& name)
	{
		auto iter = types.find(name);

		if (iter != types.end())
			return iter->second;

		auto prim_iter = primitives.find(name);

		if (prim_iter == primitives.end())
			return nullptr;

		return prim_iter->second.raw_ptr();
	}

	ast::Function *ModuleContext::get_function(const String& name)
	{
		auto iter = functions.find(name);

		return iter != functions.end()
			? iter->second
			: nullptr;
	}

	ast::Member *TypeContext::get_member(const String& name)
	{
		auto iter = members.find(name);

		return iter != members.end()
			? iter->second
			: nullptr;
	}

	ast::Declaration *FunctionContext::get_parameter(const String& name)
	{
		auto iter = parameters.find(name);

		return iter != parameters.end()
			? iter->second
			: nullptr;
	}

	ast::Declaration *FunctionContext::get_declaration(const String& name)
	{
		for (auto iter = blocks.rbegin(); iter != blocks.rend(); ++iter)
		{
			auto *block = *iter;
			
			auto *declaration = block->get_variable(name);

			if (declaration)
				return declaration;
		}

		return get_parameter(name);
	}

	ast::Declaration *FunctionContext::get_declaration_in_current_block(const String& name)
	{
		auto *declaration = current_block().get_variable(name);

		if (declaration != nullptr)
			return declaration;

		if (is_body_scope())
		{
			declaration = get_parameter(name);
		}

		return declaration;
	}

	ast::Declaration *BlockContext::get_variable(const String& name)
	{
		auto iter = variables.find(name);

		return iter != variables.end()
			? iter->second
			: nullptr;
	}
}
