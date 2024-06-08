#ifndef PARKA_VALIDATION_INTEGER_TYPE_CONTEXT_HPP
#define PARKA_VALIDATION_INTEGER_TYPE_CONTEXT_HPP

#include "parka/validation/TypeContext.hpp"

namespace parka::validation
{
	class IntegerTypeContext: public TypeContext
	{
	public:

		static IntegerTypeContext instance;
	
	private:

		IntegerTypeContext() = default;
		IntegerTypeContext(IntegerTypeContext&&) = default;
		IntegerTypeContext(const IntegerTypeContext&) = default;

	public:

		ir::ConversionIr* getConversionTo(const ir::TypeIr&) const;
	};
}

#endif
