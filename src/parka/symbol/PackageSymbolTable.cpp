#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/ast/Function.hpp"
#include "parka/ir/Package.hpp"
#include "parka/ir/Primitive.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"

namespace parka::validator
{
	PackageSymbolTable::PackageSymbolTable(const ast::PackageAst& ast, PackageSymbolTable *parent):
	SymbolTable(SymbolTableType::Package),
	Resolvable(ResolvableType::Package),
	_ast(ast),
	_scope(getScope(ast, parent)),
	_symbols(),
	_functions(),
	_parent(parent),
	_ir(nullptr)
	{
		// TODO: Actual error checking
		const auto isGlobalPackage = _parent == nullptr;

		if (isGlobalPackage)
		{
			for (auto *primitive : ir::Primitive::primitives)
				_symbols.insert(primitive->name(), primitive);
		}

		for (auto& mod : ast.modules())
		{
			// for (auto *strct : mod.structs())
			// 	strct->declareSelf(*this);

			for (auto *function : mod.functions())
				declare(*function);
		}

		// for (auto *package : _packages)
		// 	package->declareSelf(this);
	}

	String PackageSymbolTable::getScope(const ast::PackageAst& ast, PackageSymbolTable *parent)
	{
		if (parent == nullptr)
			return ast.name();

		auto *package = static_cast<PackageSymbolTable*>(parent);
		auto scope = String();

		scope.reserve(128);

		scope += package->_scope;
		scope += "::";
		scope += ast.name();

		return scope;
	}

	bool PackageSymbolTable::declare(const Declarable& declarable)
	{
		// TODO: Invalidate symbol on failure, better error
		const auto& identifier = declarable.identifier().text();
		auto result = false;

		switch (declarable.declarableType)
		{
			// case DeclarableType::Struct:
			// 	break;

			case DeclarableType::Function:
			{
				auto *ast = static_cast<const ast::FunctionAst*>(&declarable);
				auto& resolvable = _functions.push(FunctionSymbolTable(*ast, this));
				
				if (_symbols.insert(identifier, &resolvable))
					return true;

				break;
			}

			// case DeclarableType::Variable:
			// 	break;

			// case DeclarableType::Parameter:
			// 	break;

			// case DeclarableType::Member:
			// 	break;

			default:
				break;
		}

		// TODO: Show previous
		log::error("Name `$` is already declared in this package.", identifier);

		return result;
	}

	Resolvable *PackageSymbolTable::findInitial(const ast::Identifier& identifier)
	{
		const auto& name = identifier.text();
		auto *package = this;

		do
		{
			auto *entry = package->find(identifier);

			if (entry != nullptr)
				return entry;

			if (package->name() == name)
				return package;

			package = package->_parent;
		}
		while (package != nullptr);

		return nullptr;
	}

	Resolvable *PackageSymbolTable::findAbsolute(const ast::Identifier& identifier)
	{
		auto *package = this;
		auto *parent = _parent;
		
		while (parent != nullptr)
		{
			package = parent;
			parent = package->_parent;
		}

		assert(package->name().empty() && "Package with no parent must be the global package");

		auto *entry = package->find(identifier);

		return entry;
	}

	Resolvable *PackageSymbolTable::find(const ast::Identifier& identifier)
	{
		auto result = _symbols.find(identifier.text());

		if (result != nullptr)
			return *result;

		return nullptr;
	}

	Resolution *PackageSymbolTable::resolve(const ast::QualifiedIdentifier& qualifiedIdentifier)
	{
		// TODO: Optimize absolute package
		const auto& first = qualifiedIdentifier[0];
		auto *entry = qualifiedIdentifier.isAbsolute()
			? findInitial(first)
			: findAbsolute(first);

		for (usize i = 1; i < qualifiedIdentifier.length(); ++i)
		{
			if (entry == nullptr)
				break;

			const auto& identifier = qualifiedIdentifier[i];
			auto *table = dynamic_cast<SymbolTable*>(entry);

			if (table == nullptr)
			{
				log::error("Unable to resolve $ in $ $.", identifier, entry->resolvableType, entry->name());
				return nullptr;
			}

			entry = table->find(identifier);
		}

		if (entry != nullptr)
			log::notImplemented(here());
			// return entry->context();

		// TODO: Use index to shorten the symbol so it is more specific what could not be found
		log::error("Unable to find $ in this scope.", qualifiedIdentifier);

		return nullptr;
	}

	std::ostream& operator<<(std::ostream& out, const PackageSymbolTable& validator)
	{
		auto indent = Indent(out);

		out << indent;

		if (validator.name().empty())
		{
			out << "global\n";
		}
		else
		{
			out << "package `" << validator.name() << "`\n";
		}

		out << indent << "{\n";

		{
			auto subindent = Indent(out);

			out << subindent << "symbols\n";
			out << subindent << "{\n";

			{
				auto subsubindent = Indent(out);

				for (const auto& entry : validator._symbols)
				{
					out << subsubindent << *entry.value() << '\n';
				}

			}

			out << subindent << "}\n\n";
		}

		// for (const auto& mod : validator.modules())
		// {
		// 	out << mod << '\n';
		// }

		// for (const auto *package : validator._packages)
		// {
		// 	out << *package << '\n';
		// }

		out << indent << "}";

		return out;
	}
}
