#ifndef PARKA_AST_PACKAGE_HPP
#define PARKA_AST_PACKAGE_HPP

#include "parka/ast/module.hpp"
#include "parka/scope.hpp"
#include "parka/token.hpp"
#include "parka/util/directory.hpp"
#include "parka/util/optional.hpp"

class Package : public Entity
{
	String _symbol;
	Array<Module> _modules;

	Package(String&& symbol, Array<Module>&& modules) :
	_symbol(std::move(symbol)),
	_modules(std::move(modules))
	{}

public:

	Package(Package&&) = default;
	Package(const Package&) = delete;
	~Package() = default;

	static Optional<Package> parse(const Directory& directory, Scope& scope, const String& name);
	static bool declare(usize index);
	static bool validate(usize index);

	Token token() const { return Token(); }
	const String& symbol() const { return _symbol; }
	EntityType type() const { return EntityType::Package; }

	const auto& symbol() const { return _symbol; }
	const auto& modules() const { return _modules; }
};

#endif
