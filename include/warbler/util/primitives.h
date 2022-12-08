#ifndef WARBLER_PRIMITIVES_H
#define WARBLER_PRIMITIVES_H

// standard headers
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// unsigned integers
typedef uint8_t byte;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef uintptr_t usize;
typedef intptr_t isize;

// signed integers
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// floating point
typedef float f32;
typedef double f64;

#ifndef thread_local
#define thread_local _Thread_local
#endif

#endif
