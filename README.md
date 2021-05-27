# Grackle Programming Language
> NOTICE: This project is pre-alpha-level software and is not in a useable state as of now.
## Brief

Grackle is an easy to use language that compiles directly to readable C. The purpose for this is for direct binary compatibility with existing C libraries as well as being able to take advantage of the ubiquity of C compilers. It has mainly been made as a learning tool for myself to better understand compiler design.

## Syntax

The syntax is a mix between several langauges with the intention of making the code easy to read. Below is an example hello world program.
```
func main() -> i32
{
	print_greeting();
	return 0;
}

func print_greeting()
{
	var msg : str = "Hello, world!";
	print(msg);
}
```
## Current Status

* Lexer is functional although not all token types are implemented
* Parser is functional although not all non-terminals are implemented
* C code generation has been started

## To-Do

* Symbol mangling to allow for namespaces
* Implementation of more complex statements such as pattern matching
* Implementation of tuples
* Code generation

## License

Copyright 2021 Ike Hirzel

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
