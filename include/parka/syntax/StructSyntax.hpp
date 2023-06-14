#ifndef PARKA_SYNTAX_STRUCT_SYNTAX_HPP
#define PARKA_SYNTAX_STRUCT_SYNTAX_HPP

#include "parka/context/StructContext.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/MemberSyntax.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/type/ValueType.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class StructSyntax : public EntitySyntax
	{
		Identifier _identifier;
		Array<MemberSyntax*> _members;
		Table<String, EntitySyntax*> _symbols;
		SymbolTable *_parent;
		StructContext *_context;

	public:

		StructSyntax(Identifier&& identifier, Array<MemberSyntax*>&& members);
		StructSyntax(StructSyntax&&) = default;
		StructSyntax(const StructSyntax&) = delete;

		static StructSyntax *parse(Token& token);
		void declare(SymbolTable& parent);
		StructContext *validate();

		EntityType entityType() const { return EntityType::Struct; }
		const String& identifier() const { return _identifier.text(); }
		const auto& members() const { return _members; }

		friend std::ostream& operator<<(std::ostream& out, const StructSyntax& syntax);
	};
}

#endif
