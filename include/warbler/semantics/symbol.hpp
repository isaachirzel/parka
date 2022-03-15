#ifndef WARBLER_SEMANTICS_ATTRIBUTES
#define WARBLER_SEMANTICS_ATTRIBUTES

#include <warbler/semantics/type/definition.hpp>
#include <warbler/semantics/statement/variable.hpp>
#include <warbler/semantics/function/function_signature.hpp>
#include <warbler/semantics/function/parameter.hpp>
#include <warbler/semantics/function/function.hpp>

#include <warbler/util/primitive.hpp>
#include <warbler/util/array.hpp>
#include <warbler/util/optional.hpp>
#include <cassert>

namespace warbler::semantics
{
	enum class SymbolType
	{
		Function,
		Variable,
		Parameter,
		TypeDefinition
	};

	class Symbol
	{
		union
		{
			Variable _variable;
			Parameter* _parameter;
			Function _function;
			Definition _definition;
		};

		SymbolType _type;

	public:

		Symbol(Variable&& variable);
		Symbol(Function&& function);
		Symbol(Parameter& parameter);
		Symbol(Definition&& definition);
		Symbol(Symbol&&);
		Symbol& operator=(Symbol&&);
		Symbol(const Symbol&) = delete;
		Symbol& operator=(const Symbol&) = delete;
		~Symbol();

		SymbolType type() const { return _type; }
		const Variable& variable() const { assert(_type == SymbolType::Variable); return _variable; }
		const Parameter& parameter() const { assert(_type == SymbolType::Parameter); return *_parameter; }
		const Function& function() const { assert(_type == SymbolType::Function); return _function; }
		const Definition& definition() const { assert(_type == SymbolType::TypeDefinition); return _definition; }
	};
}

#endif