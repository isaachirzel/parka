// #ifndef SYBMOL_TABLE_ID_HPP
// #define SYBMOL_TABLE_ID_HPP

// #include "parka/symbol/SymbolTable.hpp"
// #include "parka/util/Common.hpp"

// namespace parka
// {
// 	class SymbolTableId
// 	{
// 		u32 _index;
// 		SymbolTableType _type;

// 		SymbolTableId(SymbolTableType type, usize index) :
// 		_index(index),
// 		_type(type)
// 		{}

// 	public:

// 		SymbolTableId(SymbolTableId&&) = default;
// 		SymbolTableId(const SymbolTableId&) = default;

// 		const auto& index() const { return _index; }
// 		const auto& type() const { return _type; }

// 		SymbolTableId& operator=(SymbolTableId&&) = default;
// 		SymbolTableId& operator=(const SymbolTableId&) = default;
// 		friend std::ostream& operator<<(std::ostream& out, const SymbolTableId& id);
// 		bool operator==(const SymbolTableId& other) const;
// 		const SymbolTable& operator*() const;
// 		const SymbolTable *operator->() const;
// 	};
// }

// namespace std
// {
// 	template <>
// 	struct hash<parka::SymbolTableId>
// 	{
// 		parka::usize operator()(const parka::SymbolTableId& key) const;
// 	};
// }

// #endif
