#ifndef WARBLER_UTIL_ARRAY_H
#define WARBLER_UTIL_ARRAY_H

#include "warbler/util/primitives.h"

#define Array(type) struct { type *data; usize length; usize capacity; }

#endif
