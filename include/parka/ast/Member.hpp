#ifndef PARKA_AST_MEMBER_HPP
#define PARKA_AST_MEMBER_HPP

#include "parka/ast/TypeAnnotation.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/enum/ResolvableType.hpp"
#include "parka/ir/Member.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka::ast
{
	class MemberAst
	{
		Snippet _snippet;
		Identifier _identifier;
		TypeAnnotationAst _annotation;
		bool _isPublic;

	public:

		MemberAst(const Snippet& snippet, Identifier&& identifier, TypeAnnotationAst&& annotation, bool isPublic):
		_snippet(snippet),
		_identifier(std::move(identifier)),
		_annotation(std::move(annotation)),
		_isPublic(isPublic)
		{}
		MemberAst(MemberAst&&) = default;
		MemberAst(const MemberAst&) = delete;

		const Identifier& identifier() const { return _identifier; }
		const String& name() const { return _identifier.text(); }
		const Snippet& snippet() const { return _snippet; }
		const auto& annotation() const { return _annotation; }
		const auto& isPublic() const { return _isPublic; }
	};
}

#endif
