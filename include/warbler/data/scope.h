#ifndef SCOPE_H
#define SCOPE_H

// local includes
#include <grackle/data/symbol.h>

// standard library
#include <unordered_map>

namespace grackle
{
	class Scope
	{
	private: // members

		Symbol *_symbol;
		std::unordered_map<std::string, Symbol*> _members;

	public: // methods

		Scope() :
		_symbol(nullptr),
		_members()
		{}

		Scope(Scope&&) = default;
		Scope(const Scope&) = default;
		~Scope() = default;

		const auto& symbol() const { return *_symbol; }
		const auto& members() const { return _members;
	};
}

#endif