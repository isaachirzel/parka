#ifndef WARBLER_AST_CONSTANT_HPP
#define WARBLER_AST_CONSTANT_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>
namespace warbler
{
	enum ConstantType
	{
		CONSTANT_CHARACTER,
		CONSTANT_STRING,
		CONSTANT_INTEGER,
		CONSTANT_FLOAT, 
		CONSTANT_BOOLEAN
	};

	class Constant
	{
	private:

		union
		{
			String _string;
			i64 _integer;
			f64 _floating;
			u32 _character;
			bool _boolean;
		};

		ConstantType _type;

	public:

		Constant(String&& string);
		Constant(i64 integer);
		Constant(f64 floatingpt);
		Constant(u32 character);
		Constant(bool boolean);
		Constant(Constant&& other);
		Constant(const Constant& other);
		~Constant();

		static Result<Constant> parse(TokenIterator& iter);

	void print_tree(u32 depth = 0) const;

		Constant& operator=(Constant&& other);
		Constant& operator=(const Constant& other);
	};
}
#endif