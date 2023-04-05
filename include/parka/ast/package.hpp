#ifndef PARKA_AST_PACKAGE_HPP
#define PARKA_AST_PACKAGE_HPP

#include "parka/ast/identifier.hpp"
#include "parka/ast/module.hpp"
#include "parka/ast/qualified_identifier.hpp"
#include "parka/symbol/entity.hpp"
#include "parka/symbol/entity_id.hpp"
#include "parka/symbol/scope.hpp"
#include "parka/token.hpp"
#include "parka/util/array.hpp"
#include "parka/util/directory.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/project.hpp"
#include <stdexcept>

class Package : public Entity
{
	String _identifier;
	Array<Module> _modules;
	Array<EntityId> _packageIds;
	// Validation
	Optional<EntityId> _parentPackageId;
	Table<String, EntityId> _symbols;

	Package(Array<EntityId>&& packageIds) :
	_identifier(),
	_modules(),
	_packageIds(std::move(packageIds)),
	_parentPackageId(),
	_symbols()
	{}

	Package(String&& identifier, Array<Module>&& modules, Array<EntityId>&& packageIds) :
	_identifier(std::move(identifier)),
	_modules(std::move(modules)),
	_packageIds(std::move(packageIds))
	{}

	Package& getGlobalPackage();
	void declarePackage(const EntityId& packageId);
	bool declareEntity(const EntityId& entityId);
	bool declareEntities(const Array<EntityId>& entityIds);
	bool declareModule(const Module& mod);
	Optional<EntityId> resolve(const QualifiedIdentifier& identifier, usize index);

	static Optional<EntityId> parse(const Directory& directory, const String& name);
	
public:

	Package(Package&&) = default;
	Package(const Package&) = delete;
	~Package() = default;

	static Optional<EntityId> parse(const Project& project);

	bool declare();
	bool validate();
	bool validate(const EntityId& parentPackageId);
	Optional<EntityId> find(const Identifier& identifier);
	Optional<EntityId> findGlobal(const Identifier& identifier);
	Optional<EntityId> resolve(const QualifiedIdentifier& identifier);

	const String& identifier() const { return _identifier; }
	EntityType type() const { return EntityType::Package; }

	const auto& modules() const { return _modules; }
};

#endif
