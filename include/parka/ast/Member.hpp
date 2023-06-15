#ifndef PARKA_SYNTAX_MEMBER_SYNTAX_HPP
#define PARKA_SYNTAX_MEMBER_SYNTAX_HPP

#include "parka/ast/Entity.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/ast/Identifier.hpp"

namespace parka
{
	class MemberContext : public EntityContext
	{
	public:

		EntityType entityType() const { return EntityType::Member; }
	};

	class MemberSyntax : public EntitySyntax
	{
		Identifier _identifier;
		TypeAnnotationSyntax _annotation;
		bool _isPublic;
		SymbolTable *_parent;
		// TODO: Add read/write count

	public:

		MemberSyntax(Identifier&& symbol, TypeAnnotationSyntax&& annotation, bool isPublic);
		MemberSyntax(MemberSyntax&&) = default;
		MemberSyntax(const MemberSyntax&) = delete;

		static MemberSyntax *parse(Token& token);
		bool declareSelf(SymbolTable& parent);
		MemberContext *validate();
		EntityContext *context() { return validate(); }
		String getSymbol() const;

		const Identifier& identifier() const { return _identifier; }
		const String& name() const { return _identifier.text(); }
		EntityType entityType() const { return EntityType::Member; }
		const auto& token() const { return _identifier.token(); }
		const auto& annotation() const { return _annotation; }
		const auto& isPublic() const { return _isPublic; }
	};
}

#endif
