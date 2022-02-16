#include <warbler/semantics/context.hpp>

#include <cassert>

namespace warbler::semantics
{
	const Table<PrimitiveType> ModuleContext::primitives
	{
		{ "i8", PRIMITIVE_I8 },
		{ "i16", PRIMITIVE_I16 },
		{ "i32", PRIMITIVE_I32 },
		{ "i64", PRIMITIVE_I64 },
		{ "isize", PRIMITIVE_ISIZE },

		{ "u8", PRIMITIVE_U8 },
		{ "u16", PRIMITIVE_U16 },
		{ "u32", PRIMITIVE_U32 },
		{ "u64", PRIMITIVE_U64 },
		{ "usize", PRIMITIVE_USIZE },

		{ "b8", PRIMITIVE_B8 },
		{ "b16", PRIMITIVE_B16 },
		{ "b32", PRIMITIVE_B32 },
		{ "b64", PRIMITIVE_B64 },

		{ "f32", PRIMITIVE_F32 },
		{ "f64", PRIMITIVE_F64 },

		{ "char", PRIMITIVE_CHAR},
		{ "bool", PRIMITIVE_BOOL},
		{ "str", PRIMITIVE_STR}
	};

	ast::Type *ModuleContext::get_type(const String& name)
	{
		auto iter = types.find(name);

		return iter != types.end()
			? iter->second
			: nullptr;
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
		ast::Declaration *declaration = nullptr;

		if (blocks.empty())
		{
			declaration = get_parameter(name);

			if (declaration == nullptr)
			{
				declaration = body->get_variable(name);
			}
		}
		else
		{
			auto *scope = blocks.back();
			
			declaration = scope->get_variable(name);
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
