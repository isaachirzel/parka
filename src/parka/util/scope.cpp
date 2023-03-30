#include "parka/util/scope.hpp"
#include "parka/util/string.hpp"

#include <cstring>
#include <cassert>



usize getTokenCount(const char *key)
{
	usize count = 0;
	
	while (true)
	{
		switch (*key)
		{
			case '\0':
				count += 1;
				break;

			case ':':
				assert(key[1] == ':');
				count += 1;
				key += 2;
				continue;

			default:
				key += 1;
				continue;
		}
		break;
	}

	return count;
}

Scope Scope::from(const String& symbol)
{
	auto scope = Scope(getTokenCount(symbol.c_str()));
	// TODO: Make this safe
	char token[128];
	usize tokenLength = 0;

	for (usize i = 0; i < symbol.size() + 1; ++i)
	{
		switch (symbol[i])
		{
			case ':':
				token[tokenLength] = '\0';
				i += 1;
				scope.push(token);
				tokenLength = 0;
				continue;

			case '\0':
				token[tokenLength] = '\0';
				scope.push(token);
				tokenLength = 0;
				break;

			default:
				token[tokenLength] = symbol[i];
				tokenLength += 1;
				continue;
		}
	}

	return scope;
}

bool Scope::contains(const String& name)
{
	for (const auto& value : _names)
	{
		if (value == name)
			return true;
	}

	return false;
}

void Scope::push(String&& name)
{
	_names.push(name);
}

void Scope::pop()
{
	_names.pop();
}

void Scope::clear()
{
	_names.clear();
}

String Scope::createSymbolN(const String& identifier, usize n) const
{
	assert(n <= _names.length());
	auto symbol = String();

	symbol.reserve(255);

	for (usize i = 0; i < n; ++i)
	{
		symbol += _names[i];
		symbol += "::";
	}

	symbol += identifier;

	return symbol;
}

String Scope::createSymbol(const String& identifier) const
{
	return createSymbolN(identifier, _names.length());
}
