# Parka Programming Language

# Brief

Parka aims to be an easy to use, fast, and safe language with native C inter-op and the ability to be run as a scripting language. A primary backend has not been chosen, but interpretation is on its way to full implementation.

# Purpose

This project has primary been made as a learning tool for myself to better understand compiler design, programming language principles, and software development.

# Syntax

The syntax is a mix between several langauges such as GO, Rust, and C++. This is with the intention of making the code easy to read for this familiar with C-like languages but also to allow for easier to write and read code.

The syntax of a hello world program is as follows:

```
import std::io;

function main()
{
	var message = getGreeting();

	print(message);
}

function getGreeting(): string => "Hello, world!";

```

# License

Copyright 2024 Isaac Hirzel

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
