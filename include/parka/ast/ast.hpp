#ifndef PARKA_AST_AST_HPP
#define PARKA_AST_AST_HPP

#include "parka/symbol/entity_id.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/project.hpp"
#include "parka/util/optional.hpp"

class Ast
{
	Array<EntityId> _packageIds;

	Ast(Array<EntityId>&& packageIds) :
	_packageIds(std::move(packageIds))
	{}

public:

	Ast(Ast&&) = default;
	Ast(const Ast&) = delete;
	~Ast() = default;

	static Optional<Ast> parse(const Project& project);

	bool validate();
};

#endif
