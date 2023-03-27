#ifndef PARKA_AST_STRUCT_HPP
#define PARKA_AST_STRUCT_HPP

#include "parka/ast/member.hpp"
#include "parka/symbol/symbol_table.hpp"
#include "parka/util/array.hpp"

class Struct
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

	bool validate(SymbolTable& symbols);

	auto token() const { return _name; }
	const auto& name() const { return _name; }
	const auto& symbol() const { return _symbol; }
	const auto& members() const { return _members; }
	auto type() const { return EntityType::Struct; }
};

#endif
