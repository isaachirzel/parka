# Warbler Programming Language
> NOTICE: This project is prealpha-level and under active development. It is not currently in a
useable state.

# Brief

Warbler aims to an easy to use, fast, and safe language with native C inter-op. In the future,
support for embedding in other applications, running as a script, compilation to C, and compilation
to machine code is planned.

# Purpose

This project has primary been made as a learning tool for myself to better understand
compiler design, programming language principles, and software development in C.

# Syntax

The syntax is a mix between several langauges such as GO, Rust, and C with the intention of making
the code easy to read for this familiar with C like languages, but allow for a more modern syntax.

The syntax of a hello world program is as follows:

```
import std::io as io;

function main()
{
	var message = get_greeting();

	io::print(message);
}

function get_greeting(): char[]
{
	return "Hello, world!";
}
```

# To-Do

- Separate SymbolTable structure into contexts
- Make SymbolTable thread-safe
- Implement thread pool for tasks
- Implement while-var and if-var expression parsing, validation
- Implement hash table for performance increase
- Finish parser
- Finish validator
- Implement C generator

# License

Copyright 2023 Isaac Hirzel

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
