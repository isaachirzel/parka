#include "parka/ast/primitive.hpp"
#include "parka/util/array.hpp"
#include "parka/util/print.hpp"

Token Primitive::token() const
{
	exitWithError("Primitives do not have tokens");
}
