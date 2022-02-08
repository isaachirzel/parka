#include <warbler/semantics/context.hpp>

#include <cassert>

namespace warbler::semantics
{
	static u32 last_id = 0;

	u32 Context::generate_type_id()
	{
		last_id += 1;
		return last_id;
	}

	String Context::qualified_scope() const
	{
		String out;
		usize size = 0;

		assert(!scope.empty());

		for (const auto& mod : scope)
			size += mod.size();

		size += (scope.size() - 1) * 2;	
		out.reserve(size);

		bool is_first = true;

		for (const auto& mod : scope)
		{
			out += mod;

			if (is_first)
			{
				is_first = false;
			}
			else
			{
				out += "::";
			}
		}

		return out;
	}

	String Context::qualified_scope(const String& name) const
	{
		String out;
		usize size = 0;

		for (const auto& mod : scope)
			size += mod.size();

		size += scope.size() * 2 + name.size();
		out.reserve(size);

		for (const auto& mod : scope)
		{
			out += mod;
			out += "::";
		}

		out += name;

		return out;
	}
}
