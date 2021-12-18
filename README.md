# Warbler Programming Language
> NOTICE: This project is prealpha-level software and is not in a useable state as of now.
# Brief

Warbler aims to an easy to use, fast, and safe language with native C inter-op. This is planned to
be implemented by giving the option to compile to machine code through use of LLVM or JIT'd by use
of an inbuilt VM. This would allow warbler to be used to develop applications as well as be used as
a scripting language.

This project has primary been made as a learning tool for myself to better understand
compiler design, standard language principles, and application development in C.

# Syntax

The syntax is a mix between several langauges such as GO, Rust, and C with the intention of making
the code easy to read for this familiar with C like languages, but allow for a more modern syntax.

Below is the syntax of a hello world program.
```
import std::io;

func main()
{
	print_greeting();
}

func print_greeting()
{
	var msg = "Hello, world!";
	std::io::print(msg);
}
```
# Current Status

* Lexer is functional although not all token types are implemented. An overhaul is planned for
	greater efficiency
* Parser is currently being implemented

# To-Do

* Finish parser
* Update parser to not use hash table for operators
* AST semantic verification

# Dependencies

* [C-Utils](https://github.com/ikehirzel/c-utils)

# License

Copyright 2021 Ike Hirzel

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
