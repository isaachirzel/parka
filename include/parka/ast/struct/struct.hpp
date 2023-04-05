#ifndef PARKA_AST_STRUCT_HPP
#define PARKA_AST_STRUCT_HPP

#include "parka/ast/identifier.hpp"
#include "parka/ast/struct/member.hpp"
#include "parka/symbol/entity.hpp"
#include "parka/symbol/entity_id.hpp"
#include "parka/ast/type/type.hpp"
#include "parka/symbol/typed_entity.hpp"
#include "parka/util/array.hpp"

class Struct : public Entity
{
	Identifier _identifier;
	Array<Member> _members;

	Struct(Identifier&& identifier, Array<Member>&& members) :
	_identifier(std::move(identifier)),
	_members(std::move(members))
	{}

public:

	Struct(Struct&&) = default;
	Struct(const Struct&) = delete;
	~Struct() = default;

	static Optional<EntityId> parse(Token& token);

	bool validate(const EntityId& packageId);

	Optional<Type> getType() const;
	const String& identifier() const { return _identifier.text(); }
	const auto& members() const { return _members; }
	EntityType type() const { return EntityType::Struct; }
};

#endif
