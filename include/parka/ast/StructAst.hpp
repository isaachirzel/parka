#ifndef PARKA_AST_STRUCT_HPP
#define PARKA_AST_STRUCT_HPP

#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/MemberAst.hpp"
#include "parka/util/Array.hpp"

namespace parka::ast
{
	class StructAst
	{
		Snippet _snippet;
		IdentifierAst _identifier;
		Array<MemberAst*> _members;

	public:

		StructAst(const Snippet& snippet, IdentifierAst&& identifier, Array<MemberAst*>&& members):
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
