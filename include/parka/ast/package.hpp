#ifndef PARKA_AST_PACKAGE_HPP
#define PARKA_AST_PACKAGE_HPP

#include "parka/ast/module.hpp"
#include "parka/symbol/entity.hpp"
#include "parka/symbol/global_symbol_table.hpp"
#include "parka/symbol/scope.hpp"
#include "parka/symbol/local_symbol_table.hpp"
#include "parka/token.hpp"
#include "parka/util/directory.hpp"
#include "parka/util/optional.hpp"
#include <stdexcept>

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

	static Optional<Package> parse(const Array<File>& files, String&& symbol);

	bool declare(GlobalSymbolTable& globalSymbols);
	bool validate(GlobalSymbolTable& globalSymbols);

	Token token() const { throw std::invalid_argument("Packages do not have tokens."); }
	const String& symbol() const { return _symbol; }
	EntityType type() const { return EntityType::Package; }

	const auto& modules() const { return _modules; }
};

#endif
