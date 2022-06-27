// local headers
#include <warbler/parser.hpp>
#include <warbler/validator.hpp>
#include <warbler/util/print.hpp>
#include <warbler/c_generator.hpp>
#include <warbler/util/file.hpp>
#include <iostream>

// standard headers
#include <stdio.h>
#include <assert.h>

// TODO

const char *src =
R"==(
	function do_it()
	{
		var i: u32 = 0;
		var wow: u16 = 12;
		i = 12;
	}
)==";

using namespace warbler;

int main()
{
	auto directories = Array<Directory>();

	directories.emplace_back(Directory::from("test", File::from("in-memory-file.wb", src)));

	auto parse_res = parse(directories);

	if (!parse_res)
	{
		print_error("failed to parse source");
		return 1;
	}

	print_note("successfully parsed source");

	auto syntax = parse_res.unwrap();
	auto context_res = validate(syntax);

	if (!context_res)
	{
		print_error("errors when validating source");
		return 1;
	}
	
	auto context = context_res.unwrap();

	print_note("successfully validated source");

	auto c = generate_c_program(context);
	
	c += "int main() { return 0; }\n";

	std::cout << "Generated C:\n\n" << c << std::endl;

	if (!write_file("./output.c", c))
		return 1;

	return 0;
}