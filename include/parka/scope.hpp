#ifndef PARKA_SCOPE_HPP
#define PARKA_SCOPE_HPP

#include "parka/util/array.hpp"
#include "parka/util/primitives.hpp"
#include "parka/util/string.hpp"

class Scope
{
    Array<String> _names;

public:
    
    Scope(usize capacity);
    Scope(const String& key);
    Scope(Scope&&) = default;
    Scope(const Scope&) = delete;
    ~Scope() = default;

    bool contains(const String& name);
    void push(const String& name);
    void pop();
    void clear();
    usize count() const { return _names.size(); }

    String createSymbol(const String& identifier) const;
    String createSymbolN(const String& identifier, usize n) const;
};

#endif
