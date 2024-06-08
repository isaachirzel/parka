#include "parka/validation/IntegerTypeContext.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/Util.hpp"

namespace parka::validation
{
	IntegerTypeContext IntegerTypeContext::instance;

	ir::ConversionIr* IntegerTypeContext::getConversionTo(const ir::TypeIr& toType) const
	{
		if (toType == ir::PrimitiveIr::i32Primitive)
			return &conv<Integer, i32>();

		return nullptr;
	}
}
