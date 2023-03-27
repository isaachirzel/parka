#ifndef PARKA_SCOPE_HPP
#define PARKA_SCOPE_HPP

#include "parka/util/array.hpp"
#include "parka/util/primitives.hpp"
#include "parka/util/string.hpp"

class Scope
{
    Array<String> _names;

public:
    
    Scope(usize capacity) :
    _names(capacity)
    {}
    Scope(Scope&&) = default;
    Scope(const Scope&) = delete;
    Scope& operator=(Scope&& other) { new (this) auto(std::move(other)); return *this; }
    Scope& operator=(const Scope& other) = delete;

    static Scope from(const String& symbol);

    bool contains(const String& name);
    void push(String&& name);
    void pop();
    void clear();
    usize count() const { return _names.length(); }

    String createSymbol(const String& identifier) const;
    String createSymbolN(const String& identifier, usize n) const;
};

#endif
