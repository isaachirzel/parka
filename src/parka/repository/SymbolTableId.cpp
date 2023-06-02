// #include "parka/repository/SymbolTableId.hpp"
// #include "parka/enum/SymbolTableType.hpp"
// #include "parka/symbol/BlockSymbolTable.hpp"
// #include "parka/symbol/FunctionSymbolTable.hpp"
// #include "parka/symbol/PackageSymbolTable.hpp"
// #include "parka/symbol/SymbolTableEntry.hpp"
// #include "parka/util/Pool.hpp"
// #include "parka/util/Print.hpp"

// namespace parka
// {
// 	// TODO: Create constant that will be the max entity count for SymbolTables/entities of the same type
// 	static Pool<PackageSymbolTable> packageSymbolTables(1'000);
// 	static Pool<BlockSymbolTable> blockSymbolTables(100'000);
// 	static Pool<FunctionSymbolTable> functionSymbolTables(1'000'000);

// 	std::ostream& operator<<(std::ostream& out, const SymbolTableId& id)
// 	{
// 		out << id._type << "s[" << id._index << ']';

// 		return out;
// 	}

// 	bool SymbolTableId::operator==(const SymbolTableId& other) const
// 	{
// 		return _type == other._type && _index == other._index;
// 	}

// 	const SymbolTable& SymbolTableId::operator*() const
// 	{
// 		switch (_type)
// 		{
// 			case SymbolTableType::Block:
// 				return blockSymbolTables[_index];

// 			case SymbolTableType::Function:
// 				return functionSymbolTables[_index];

// 			case SymbolTableType::Package:
// 				return packageSymbolTables[_index];

// 			default:
// 				break;
// 		}

// 		Log::fatal("Unable to get SymbolTable with type: $", _type);
// 	}

// 	const SymbolTable *SymbolTableId::operator->() const
// 	{
// 		return &(*(*this));
// 	}
// }
