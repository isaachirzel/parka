#include "parka/ast/primitive.hpp"
#include "parka/util/array.hpp"

Token Primitive::token() const
{
	exitWithError("Primitives do not have tokens");
}
