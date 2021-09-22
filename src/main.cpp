// local includes

// standard library

#include <stdexcept>
#include <filesystem>
#include <string>
#include <fstream>

void validate_cli_args(int argc, char *argv[])
{
	if (argc != 2)
		throw std::runtime_error("invalid arguments given, expected: grackle <filename>");

	if (!std::filesystem::exists(argv[1]))
		throw std::runtime_error("file '" + std::string(argv[1]) + "' does not exist"); 
}

std::string read_file(const std::string& filepath)
{
	std::ifstream file(filepath);

	if (!file.is_open())
		throw std::runtime_error("file '" + filepath + "' failed to open");

	file.seekg(0, std::ios::end);
	auto size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::string out(size, 0);

	if (!file.read(&out[0], size))
		throw std::runtime_error("failed to read data from file: " + filepath);
	
	return out;
}

int main(int argc, char *argv[])
{
	validate_cli_args(argc, argv);

	std::string src = read_file(argv[1]);
	preprocesor(src);

// 	// preprocessing src
// 	preprocess(src);

// 	// printing src
// 	// puts(src);

// 	// lexing src
// 	lex_init();
// 	toklist_t *toks = lex(src);
// 	if (!toks) return 1;
// 	// pritning toks
// 	// print_toks(toks);

// 	// parsing src
// 	node_t *ast = parse(toks);
// 	if (!ast) goto cleanup;
	
// 	puts("\nAbstract Syntax Tree:");
// 	node_print(ast);

// 	puts("\n");
// 	// semantic analysis
// 	//if (!analyze(ast)) goto cleanup;

// 	// code generation
// 	// strlist_t *gen = generate(ast);
// 	// generate_print(gen);


// cleanup:
// 	// memory cleanup
// 	node_destroy(ast);
// 	toklist_destroy(toks);
// 	lex_cleanup();
// 	free(src);
	return 0;
}
