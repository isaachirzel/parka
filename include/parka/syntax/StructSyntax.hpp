#ifndef PARKA_SYNTAX_STRUCT_SYNTAX_HPP
#define PARKA_SYNTAX_STRUCT_SYNTAX_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/MemberSyntax.hpp"
#include "parka/data/EntitySyntax.hpp"
#include "parka/data/EntityId.hpp"
#include "parka/type/Type.hpp"
#include "parka/util/Array.hpp"

namespace parka
{
	class StructSyntax : public EntitySyntax
	{
		Identifier _identifier;
		Array<MemberSyntax> _members;

		StructSyntax(Identifier&& identifier, Array<MemberSyntax>&& members) :
		_identifier(std::move(identifier)),
		_members(std::move(members))
		{}

	public:

		StructSyntax(StructSyntax&&) = default;
		StructSyntax(const StructSyntax&) = delete;
		~StructSyntax() = default;

		static Optional<EntityId> parse(Token& token);

		bool validate(const EntityId& packageId);

		Optional<Type> getType() const;
		const String& identifier() const { return _identifier.text(); }
		const auto& members() const { return _members; }
		EntityType type() const { return EntityType::StructSyntax; }
	};
}

#endif
