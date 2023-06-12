#ifndef PARKA_SYNTAX_MEMBER_SYNTAX_HPP
#define PARKA_SYNTAX_MEMBER_SYNTAX_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class MemberSyntax : public EntitySyntax
	{
		Token _name;
		String _symbol;
		TypeAnnotationSyntax _annotation;
		bool _isPublic;
		// TODO: Add read/write count

	public:

		MemberSyntax(const Token& name, String&& symbol, TypeAnnotationSyntax&& annotation, bool isPublic);
		MemberSyntax(MemberSyntax&&) = default;
		MemberSyntax(const MemberSyntax&) = delete;

		static Optional<MemberSyntax> parse(Token& token);

		Optional<MemberSyntax> validate(SymbolTable& symbolTable) const;

		const String& identifier() const { return _symbol; }
		EntityType entityType() const { return EntityType::Member; }
		const auto& name() const { return _name; }
		const auto& annotation() const { return _annotation; }
		const auto& isPublic() const { return _isPublic; }
	};
}

#endif
