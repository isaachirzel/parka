#ifndef PARKA_AST_MEMBER_HPP
#define PARKA_AST_MEMBER_HPP

#include "parka/ast/type/type_annotation.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"



class Member
{
	Token _name;
	String _symbol;
	TypeAnnotation _annotation;
	bool _isPublic;

	// TODO: Add read/write count

	Member(const Token& name, String&& symbol, TypeAnnotation&& annotation, bool isPublic) :
	_name(name),
	_symbol(std::move(symbol)),
	_annotation(std::move(annotation)),
	_isPublic(isPublic)
	{}

public:

	Member(Member&&) = default;
	Member(const Member&) = delete;
	~Member() = default;

	static Optional<Member> parse(Token& token);

	bool validate(const EntityId& functionId);

	const auto& name() const { return _name; }
	const auto& symbol() const { return _symbol; }
	const auto& annotation() const { return _annotation; }
	const auto& isPublic() const { return _isPublic; }
};

#endif
