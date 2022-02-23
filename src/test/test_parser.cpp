#include <warbler/lexicon/tokenizer.hpp>

// local headers
#include <warbler/syntax//ast.hpp>
#include <warbler/util/print.hpp>

// standard headers
#include <stdio.h>
#include <assert.h>

//const char *src = "foo(3, 4) * 1 / 5 + 2 / hello % 3\n + 3 == 4 >= &hello";
//const char *src = "var b: int = a || b && c << 1.7 * 3;";
// const char *src =
// "func do_thing(num: i32, text: String)\n"
// "{\n"
// "	var value: f64 = 12.58 * log(234);\n"
// "}\n"
// ;
// const char *src = R"=====(

// type Person :
// struct
// {
// 	age: i32,
// 	name: String
// }

// func do_thing(arg: i32)
// {
// 	var value: i32 = arg * 3;
// 	if value == 3
// 	{
// 		var name : String = "hello";
// 	}
// 	else if value == 6
// 	{
// 		var num : f64 = 12.5;
// 	}
// 	else
// 	{
// 		print("uh oh");
// 	}
// }
// )=====";

const char *src = R"==(

	function main(argc: i32)
	{
		var value: i32 = 3;
	}

)==";

// const char *src = R"=====(

// 	type Person: struct
// 	{
// 		public age: u8,
// 		height: f64
// 	}

// 	type House: struct
// 	{
// 		owner: Person,
// 		sq_footage: u16,
// 		elevation: i32
// 	}

// 	function print_person(person: Person, persons: i32): Person
// 	{
// 		var age = 1;
// 		age[3];
// 		person.age;
// 	}

// )=====";

using namespace warbler;
using namespace warbler::syntax;

int main()
{
	lexicon::init_tokenizer();
	semantics::init_context();

	auto token_res = lexicon::tokenize("<in-memory-file>", src);

	if (!token_res)
		return token_res;

	auto tokens = token_res.unwrap();
	
	for (const auto& token : tokens)
		std::cout << token.line() << ':' << token.col() << '\t' << token << "\t\ttype: " << token.type() << std::endl;;	

	std::cout << std::endl;

	TokenIterator iter = tokens.begin();
	auto res = Module::parse(iter);

	if (!res)
	{
		error_out() << "failed to parse src" << std::endl;
		return {};
	}

	if (iter->type() != TOKEN_END_OF_FILE)
	{
		error_out(iter) << "current token is not EOF";
		error_highlight(iter);
		return 1;
	}

	auto ast = res.unwrap();

	ast.print_tree();
	std::cout << '\n';

	if (!ast.validate({ "test" }))
	{
		print_error("errors during compilation");
		return 1;
	}
	
	print_note("successfully validated ast");

	return 0;
}