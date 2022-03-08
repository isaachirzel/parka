#ifndef WARBLER_SYNTAX_CONSTANT_HPP
#define WARBLER_SYNTAX_CONSTANT_HPP

// local headers
#include <warbler/lexicon/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>
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

		lexicon::Token _token;
		ConstantType _type;

	public:

		Constant(const lexicon::Token& token, ConstantType);
		Constant(Constant&& other) = default;
		Constant(const Constant& other) = delete;

		static Result<Constant> parse(lexicon::Token& token);

		bool validate(semantics::SymbolTable& symbols);
		void print_tree(u32 depth = 0) const;

		const lexicon::Token& token() const { return _token; }

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
