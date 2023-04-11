#ifndef PARKA_SYNTAX_MEMBER_SYNTAX_HPP
#define PARKA_SYNTAX_MEMBER_SYNTAX_HPP

#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class MemberSyntax
	{
		Token _name;
		String _symbol;
		TypeAnnotationSyntax _annotation;
		bool _isPublic;

		// TODO: Add read/write count

		MemberSyntax(const Token& name, String&& symbol, TypeAnnotationSyntax&& annotation, bool isPublic) :
		_name(name),
		_symbol(std::move(symbol)),
		_annotation(std::move(annotation)),
		_isPublic(isPublic)
		{}

	public:

		MemberSyntax(MemberSyntax&&) = default;
		MemberSyntax(const MemberSyntax&) = delete;
		~MemberSyntax() = default;

		static Optional<MemberSyntax> parse(Token& token);

		const auto& name() const { return _name; }
		const auto& symbol() const { return _symbol; }
		const auto& annotation() const { return _annotation; }
		const auto& isPublic() const { return _isPublic; }
	};
}

#endif
