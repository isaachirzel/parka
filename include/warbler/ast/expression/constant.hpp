#ifndef WARBLER_AST_CONSTANT_HPP
#define WARBLER_AST_CONSTANT_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/semantics/context.hpp>
#include <warbler/ast/expression/expression.hpp>

namespace warbler::ast
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

		Location _location;

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

		Constant(const Location& location, String&& string);
		Constant(const Location& location, i64 integer);
		Constant(const Location& location, f64 floatingpt);
		Constant(const Location& location, u32 character);
		Constant(const Location& location, bool boolean);
		Constant(Constant&& other);
		Constant(const Constant& other) = delete;
		~Constant();

		static Result<Constant> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;

		Type *get_type() { return &_type; }
		const Location& location() const { return _location; }

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
