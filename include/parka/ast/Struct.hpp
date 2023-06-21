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
	class PackageAst;

	class StructAst : public Declarable, public SymbolTable
	{
		Snippet _snippet;
		Identifier _identifier;
		Array<MemberAst*> _members;
		Table<String, Resolvable*> _symbols;
		PackageAst *_parent;
		ir::StructIr *_context;

	public:

		StructAst(const Snippet& snippet, Identifier&& identifier, Array<MemberAst*>&& members) :		
		Declarable(DeclarableType::Struct, ResolvableType::Struct),
		SymbolTable(SymbolTableType::Struct),
		_snippet(snippet),
		_identifier(std::move(identifier)),
		_members(std::move(members)),
		_symbols(),
		_parent(nullptr),
		_context(nullptr)
		{}
		StructAst(StructAst&&) = default;
		StructAst(const StructAst&) = delete;

		bool declare(Declarable& declarable);
		bool declareSelf(PackageAst& parent);
		Resolvable *find(const Identifier& identifier);
		Resolution *resolve(const QualifiedIdentifier& identifier);
		String getSymbol() const;

		const Snippet& snippet() const { return _snippet; }
		const String& name() const { return _identifier.text(); }
		const Identifier& identifier() const { return _identifier; }
		const auto& members() const { return _members; }

		friend std::ostream& operator<<(std::ostream& out, const StructAst& syntax);
	};
}

#endif
