// local headers
#include <warbler/syntax/ast.hpp>
#include <warbler/util/print.hpp>
#include <warbler/semantics/ast.hpp>

// standard headers
#include <stdio.h>
#include <assert.h>

const char *src = R"==(

	function main(argc: i32)
	{
		var value: i32 = 3;
	}

)==";

using namespace warbler;

int main()
{
	auto file = source::File::from(src);
	auto syntax = syntax::Ast::parse(file);

	if (!syntax)
	{
		print_error("failed to parse src");
		return 1;
	}

	auto syntax_tree = syntax.unwrap();

	auto context = semantics::Ast::validate(syntax_tree);

	if (!context)
	{
		print_error("errors when validating source");
		return 1;
	}

	auto ast = context.unwrap();
	// auto ast = semantics::Ast::validate(parse_tree);

	// if (!ast)
	// {
	// 	print_error("error(s) when validating src");
	// 	return 1;
	// }
	
	print_note("successfully validated ast");

	return 0;
}