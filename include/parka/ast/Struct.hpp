#ifndef PARKA_SYNTAX_STRUCT_SYNTAX_HPP
#define PARKA_SYNTAX_STRUCT_SYNTAX_HPP

#include "parka/ast/Identifier.hpp"
#include "parka/enum/SymbolTableType.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Member.hpp"
#include "parka/ast/Entity.hpp"
#include "parka/type/ValueType.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class PackageSyntax;

	class StructContext : public EntityContext
	{
		String _symbol;

	public:

		StructContext(String&& symbol);
		StructContext(StructContext&&) = default;
		StructContext(const StructContext&) = delete;

		static StructContext *validate();
		
		EntityType type() const { return EntityType::Struct; }
		const String& symbol() const { return _symbol; }
	};

	class StructSyntax : public EntitySyntax, public SymbolTable
	{
		Identifier _identifier;
		Array<MemberSyntax*> _members;
		Table<String, EntityEntry*> _symbols;
		PackageSyntax *_parent;
		StructContext *_context;

	public:

		StructSyntax(Identifier&& identifier, Array<MemberSyntax*>&& members);
		StructSyntax(StructSyntax&&) = default;
		StructSyntax(const StructSyntax&) = delete;

		static StructSyntax *parse(Token& token);
		bool declare(EntitySyntax& entity);
		bool declareSelf(PackageSyntax& parent);
		EntityEntry *find(const Identifier& identifier);
		EntityContext *resolve(const QualifiedIdentifier& identifier);
		StructContext *validate();
		EntityContext *context() { return validate(); }
		String getSymbol() const;

		SymbolTableType symbolTableType() const { return SymbolTableType::Struct; }
		EntityType entityType() const { return EntityType::Struct; }
		const String& name() const { return _identifier.text(); }
		const Identifier& identifier() const { return _identifier; }
		const auto& members() const { return _members; }

		friend std::ostream& operator<<(std::ostream& out, const StructSyntax& syntax);
	};
}

#endif
