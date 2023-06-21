#ifndef PARKA_AST_MEMBER_HPP
#define PARKA_AST_MEMBER_HPP

#include "parka/ast/TypeAnnotation.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/enum/DeclarableType.hpp"
#include "parka/enum/ResolvableType.hpp"
#include "parka/enum/ResolvableType.hpp"
#include "parka/ir/Member.hpp"
#include "parka/symbol/Declarable.hpp"

namespace parka::ast
{
	class MemberAst : public Declarable
	{
		Snippet _snippet;
		Identifier _identifier;
		TypeAnnotationAst _annotation;
		bool _isPublic;
		SymbolTable *_parent;
		// TODO: Add read/write count

	public:

		MemberAst(const Snippet& snippet, Identifier&& identifier, TypeAnnotationAst&& annotation, bool isPublic) :
		Declarable(DeclarableType::Member, ResolvableType::Member),
		_snippet(snippet),
		_identifier(std::move(identifier)),
		_annotation(std::move(annotation)),
		_isPublic(isPublic)
		{}
		MemberAst(MemberAst&&) = default;
		MemberAst(const MemberAst&) = delete;

		bool declareSelf(SymbolTable& parent);
		String getSymbol() const;

		const Identifier& identifier() const { return _identifier; }
		const String& name() const { return _identifier.text(); }
		const Snippet& snippet() const { return _snippet; }
		const auto& annotation() const { return _annotation; }
		const auto& isPublic() const { return _isPublic; }
	};
}

#endif
