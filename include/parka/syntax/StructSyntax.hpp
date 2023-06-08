#ifndef PARKA_SYNTAX_STRUCT_SYNTAX_HPP
#define PARKA_SYNTAX_STRUCT_SYNTAX_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/MemberSyntax.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/type/ValueType.hpp"
#include "parka/util/Array.hpp"

namespace parka
{
	class StructSyntax : public EntitySyntax
	{
		Identifier _identifier;
		Array<MemberSyntax> _members;

	private:

		StructSyntax(Identifier&& identifier, Array<MemberSyntax>&& members) :
		_identifier(std::move(identifier)),
		_members(std::move(members))
		{}

	public:

		StructSyntax(StructSyntax&&) = default;
		StructSyntax(const StructSyntax&) = delete;

		static const StructSyntax *parse(Token& token);

		EntityType type() const { return EntityType::Struct; }
		const String& identifier() const { return _identifier.text(); }
		const auto& members() const { return _members; }
	};
}

#endif
