#ifndef GULL_ASSERT_H
#define GULL_ASSERT_H

#include <assert.h>

#ifdef DEBUG_MODE
#define ASSERT(x) assert(x)
#else
#define ASSERT(x)
#endif

#endif
