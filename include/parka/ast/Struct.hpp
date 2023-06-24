#ifndef PARKA_AST_STRUCT_HPP
#define PARKA_AST_STRUCT_HPP

#include "parka/ast/Identifier.hpp"
#include "parka/enum/ResolvableType.hpp"
#include "parka/enum/ResolvableType.hpp"
#include "parka/enum/SymbolTableType.hpp"
#include "parka/ir/Struct.hpp"
#include "parka/symbol/Declarable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Member.hpp"
#include "parka/ir/ValueType.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Table.hpp"

namespace parka::ast
{
	class StructAst : public Declarable
	{
		Snippet _snippet;
		Identifier _identifier;
		Array<MemberAst*> _members;

	public:

		StructAst(const Snippet& snippet, Identifier&& identifier, Array<MemberAst*>&& members):
		Declarable(DeclarableType::Struct),
		_snippet(snippet),
		_identifier(std::move(identifier)),
		_members(std::move(members))
		{}
		StructAst(StructAst&&) = default;
		StructAst(const StructAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const String& name() const { return _identifier.text(); }
		const Identifier& identifier() const { return _identifier; }
		const auto& members() const { return _members; }
	};
}

#endif
