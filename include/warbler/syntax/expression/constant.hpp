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
	enum class ConstantType
	{
		Character,
		String,
		Integer,
		Hexadecimal,
		Binary,
		Octal,
		Float,
		BooleanTrue,
		BooleanFalse
	};

	class Constant : public Expression
	{
	private:

		source::Location _location;
		ConstantType _type;

	public:

		Constant(const source::Location& location, ConstantType);
		Constant(Constant&& other) = default;
		Constant(const Constant& other) = delete;

		static Result<Constant> parse(lexicon::TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;

		const source::Location& location() const { return _location; }

		Constant& operator=(Constant&& other) = default;
		Constant& operator=(const Constant& other) = delete;
	};
}

/*

TokenArray - stores textual data

Constant - stores parsed textual data

ConstantIR 


*/

#endif
