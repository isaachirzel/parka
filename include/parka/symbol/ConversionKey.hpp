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
		ConversionKey& operator=(ConversionKey&&) = default;
		ConversionKey& operator=(const ConversionKey&) = default;

		bool operator==(const ConversionKey& other) const;


		friend struct std::hash<ConversionKey>;
	};
}

template <>
struct std::hash<parka::ConversionKey>
{
	std::size_t operator()(const parka::ConversionKey& key) const;
};

#endif
