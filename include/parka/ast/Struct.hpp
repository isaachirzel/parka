#ifndef PARKA_AST_STRUCT_HPP
#define PARKA_AST_STRUCT_HPP

#include "parka/ast/Identifier.hpp"
#include "parka/ast/Member.hpp"
#include "parka/util/Array.hpp"

namespace parka::ast
{
	class StructAst
	{
		Snippet _snippet;
		Identifier _identifier;
		Array<MemberAst*> _members;

	public:

		StructAst(const Snippet& snippet, Identifier&& identifier, Array<MemberAst*>&& members):
			_snippet(snippet),
			_identifier(std::move(identifier)),
			_members(std::move(members))
		{}
		StructAst(StructAst&&) = default;
		StructAst(const StructAst&) = delete;

		const auto& snippet() const { return _snippet; }
		const auto& identifier() const { return _identifier; }
		const auto& members() const { return _members; }
	};
}

#endif
