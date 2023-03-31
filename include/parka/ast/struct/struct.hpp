#ifndef PARKA_AST_STRUCT_HPP
#define PARKA_AST_STRUCT_HPP

#include "parka/ast/struct/member.hpp"
#include "parka/symbol/entity.hpp"
#include "parka/symbol/local_symbol_table.hpp"
#include "parka/ast/type/type.hpp"
#include "parka/util/array.hpp"

class Struct : public Entity
{
	Token _name;
	String _symbol;
	Array<Member> _members;

	Struct(const Token& name, String&& symbol, Array<Member>&& members) :
	_name(name),
	_symbol(std::move(symbol)),
	_members(std::move(members))
	{}

public:

	Struct(Struct&&) = default;
	Struct(const Struct&) = delete;
	~Struct() = default;

	static Optional<EntityId> parse(Token& token, const String& package);

	bool validate(LocalSymbolTable& symbols);

	Token token() const { return _name; }
	const auto& name() const { return _name; }
	const String& symbol() const { return _symbol; }
	const auto& members() const { return _members; }
	EntityType type() const { return EntityType::Struct; }
};

#endif
