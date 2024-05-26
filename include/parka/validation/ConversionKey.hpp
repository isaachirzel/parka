#ifndef PARKA_VALIDATION_CONVERSION_KEY_HPP
#define PARKA_VALIDATION_CONVERSION_KEY_HPP

#include "parka/ir/TypeIr.hpp"

namespace parka::validation
{
	class ConversionKey
	{
		const ir::TypeIr* _to;
		const ir::TypeIr* _from;

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
struct std::hash<parka::validation::ConversionKey>
{
	std::size_t operator()(const parka::validation::ConversionKey& key) const;
};

#endif
