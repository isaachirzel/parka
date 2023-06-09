#ifndef PARKA_CONTEXT_PARAMETER_CONTEXT_HPP	
#define PARKA_CONTEXT_PARAMETER_CONTEXT_HPP	

#include "parka/repository/EntityContext.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/syntax/ParameterSyntax.hpp"
#include "parka/type/ValueType.hpp"

namespace parka
{
	class ParameterContext : public EntityContext
	{
		ValueType _type;
		bool _isMutable;

	private:

		ParameterContext(ValueType&& type, bool isMutable);

	public:

		ParameterContext(ParameterContext&&) = default;
		ParameterContext(const ParameterContext&) = delete;

		static ParameterContext *validate(const ParameterSyntax& syntax, FunctionSymbolTable& symbolTable);
	};
}

#endif
