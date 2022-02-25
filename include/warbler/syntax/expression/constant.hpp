#ifndef WARBLER_SYNTAX_CONSTANT_HPP
#define WARBLER_SYNTAX_CONSTANT_HPP

// local headers
#include <warbler/lexicon/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/semantics/context.hpp>
#include <warbler/syntax/expression/expression.hpp>

namespace warbler::syntax
{
	enum ConstantType
	{
		CONSTANT_CHARACTER,
		CONSTANT_STRING,
		CONSTANT_INTEGER,
		CONSTANT_FLOAT, 
		CONSTANT_BOOLEAN
	};

	class Constant : public Expression
	{
	private:

		source::Location _location;

		union
		{
			String _string;
			i64 _integer;
			f64 _floating;
			u32 _character;
			bool _boolean;
		};

		ConstantType _constant_type;
		Type _type;

	public:

		Constant(const source::Location& location, String&& string);
		Constant(const source::Location& location, i64 integer);
		Constant(const source::Location& location, f64 floatingpt);
		Constant(const source::Location& location, u32 character);
		Constant(const source::Location& location, bool boolean);
		Constant(Constant&& other);
		Constant(const Constant& other) = delete;
		~Constant();

		static Result<Constant> parse(lexicon::TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;

		Type *get_type() { return &_type; }
		const source::Location& location() const { return _location; }

		Constant& operator=(Constant&& other);
		Constant& operator=(const Constant& other) = delete;
	};
}

/*

TokenArray - stores textual data

Constant - stores parsed textual data

ConstantIR 


*/

#endif
