# C Utils

> NOTICE: These c utils are pre alpha level software and are mainly maintained
as needed by myself

# Brief

C-utils is a simple set of utility functions / data structures created to aid in
the making of other projects. The purpose is to abstract away some of the more
tedious procedures in C programming.

# Features and Current Status

As of right now, there are 3 main portions of c-utils:
- list.h: A dynamic array implementation
- table.h: A hash table implementation using open-addressing / quadratic-probing
- file.h: A set of convenience functions for file i/o


Data structures in c-utils achieve a form of type-genericness through use of the
preprocessor.

# Usage of Data Structures

In order to use the type generic data structures, a header needs to be created
for the specific implementation.

Below is an example of implementing an dynamic integer array using list.h

```
// intlist.h - a user defined header
#ifndef INTLIST_H
#define INTLIST_H

#define HIRZEL_CONTAINER_ITEM int
#define HIRZEL_CONTAINER_NAME intlist
#include <hirzel/util/list.h>

#endif
```

Once this header has been defined, it must be implemented in a source file of
the user's choosing. Below is an example of this.
```
// main.c - a user defined source file

// if you don't want this to affect other includes, it must be undef'd afterward
#define HIRZEL_IMPLEMENT
#include "intlist.h"
#undef HIRZEL_IMPLEMENT


int main(void)
{
	// basic usage of the data structure
	intlist_t *l = intlist_create();
	intlist_push(l, 3);
	intlist_push(l, 5);
	inlist_destroy(l);

	return 0;
}
```



# To Do

Nothing as of now

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
