// local headers
#include <warbler/parser.hpp>
#include <warbler/validator.hpp>
#include <warbler/util/print.hpp>

// standard headers
#include <stdio.h>
#include <assert.h>

// TODO

const char *src =
R"==(

	struct String
	{
		length: u64
	}
	
	struct House
	{
		owner: String
	}

	struct Person
	{
		age: u32,
		home: House,
		sq_footage: String
	}
)==";

using namespace warbler;

int main()
{
	auto directories = Array<Directory>();

	directories.emplace_back(Directory::from("mem", File::from("in-memory-file.wb", src)));

	auto parse_res = parse(directories);

	if (!parse_res)
	{
		print_error("failed to parse source");
		return 1;
	}

	auto syntax = parse_res.unwrap();
	auto context_res = validate(syntax);

	if (!context_res)
	{
		print_error("errors when validating source");
		return 1;
	}
	
	print_note("successfully validated ast");

	return 0;
}