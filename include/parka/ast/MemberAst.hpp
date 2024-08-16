#ifndef PARKA_AST_MEMBER_HPP
#define PARKA_AST_MEMBER_HPP

#include "parka/ast/TypeAnnotationAst.hpp"
#include "parka/ast/IdentifierAst.hpp"

namespace parka::ast
{
	class MemberAst
	{
		fs::FileSnippet _snippet;
		IdentifierAst _identifier;
		TypeAnnotationAst _annotation;
		bool _isPublic;

	public:

		MemberAst(const fs::FileSnippet& snippet, IdentifierAst&& identifier, TypeAnnotationAst&& annotation, bool isPublic):
			_snippet(snippet),
			_identifier(std::move(identifier)),
			_annotation(std::move(annotation)),
			_isPublic(isPublic)
		{}
		MemberAst(MemberAst&&) = default;
		MemberAst(const MemberAst&) = delete;

		const IdentifierAst& identifier() const { return _identifier; }
		const String& name() const { return _identifier.text(); }
		const fs::FileSnippet& snippet() const { return _snippet; }
		const auto& annotation() const { return _annotation; }
		const auto& isPublic() const { return _isPublic; }
	};
}

#endif
