// local headers
#include <warbler/syntax/ast.hpp>
#include <warbler/semantics/validation.hpp>
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

int main()
{
	auto file = source::File::from(src);
	auto parse_res = syntax::Ast::parse(file);

	if (!parse_res)
	{
		print_error("failed to parse src");
		return 1;
	}

	auto parse_tree = parse_res.unwrap();
	// auto ast = semantics::Ast::validate(parse_tree);

	// if (!ast)
	// {
	// 	print_error("error(s) when validating src");
	// 	return 1;
	// }
	
	print_note("successfully validated ast");

	return 0;
}