#ifndef PARKA_AST_AST_HPP
#define PARKA_AST_AST_HPP

#include "parka/node/entity_id.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/util/project.hpp"
#include "parka/util/optional.hpp"

class Ast
{
	EntityId _globalPackageId;

	Ast(const EntityId& globalPackageId) :
	_globalPackageId(globalPackageId)
	{}

public:

	Ast(Ast&&) = default;
	Ast(const Ast&) = delete;
	~Ast() = default;

	static Optional<Ast> parse(const Project& project);

	bool validate();
};

#endif
