#ifndef PARKA_SYMBOL_CONVERSION_KEY_HPP
#define PARKA_SYMBOL_CONVERSION_KEY_HPP

#include "parka/ir/TypeIr.hpp"

namespace parka
{
	class ConversionKey
	{
		ir::TypeIr _to;
		ir::TypeIr _from;

	public:

		ConversionKey();
		ConversionKey(const ir::TypeIr& to, const ir::TypeIr& from);
		ConversionKey(ConversionKey&&) = default;
		ConversionKey(const ConversionKey&) = default;

		bool operator==(const ConversionKey& other) const;

		ConversionKey& operator=(ConversionKey&&) = default;
		ConversionKey& operator=(const ConversionKey&) = default;

		friend struct std::hash<ConversionKey>;
	};
}

template <>
struct std::hash<parka::ConversionKey>
{
	std::size_t operator()(const parka::ConversionKey& key) const
	{
		auto typeHasher = std::hash<parka::ir::TypeIr>();

		return typeHasher(key._to) ^ typeHasher(key._from);
	}
};

#endif
