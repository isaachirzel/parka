#ifndef WARBLER_SEMANTICS_ATTRIBUTES
#define WARBLER_SEMANTICS_ATTRIBUTES

#include <warbler/util/array.hpp>

namespace warbler::syntax
{
	class TypeDefinition;
};

namespace warbler::semantics
{
	class Type
	{
	private:

		Array<bool> _ptr_info;
		syntax::TypeDefinition *_definition;

	public:

		Type(const Array<bool>& ptr_info, syntax::TypeDefinition *definition);

		const Array<bool>& ptr_info() const { return _ptr_info; }
		const syntax::TypeDefinition *definition() const { return _definition; }
	};

	enum class State
	{
		Declared,
		Defined,
		Invalid
	};

	// enum class DefinitionType
	// {
	// 	Function,
	// 	Parameter,
	// 	Variable
	// };

	// struct Definition
	// {
	// 	DefinitionType type;

	// 	union
	// 	{
	// 		Function *function;
	// 		Parameter *para
	// 	};
	// };


	struct Attributes
	{
		Type type;
		State _state;
		//Value _value;

		Attributes(Type&& type, State state);
	};
}

#endif