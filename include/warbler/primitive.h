#ifndef WARBLER_PRIMITIVE_H
#define WARBLER_PRIMITIVE_H

// standard headers
#include <stdint.h>

// unsigned integers

typedef uint8_t		byte;
typedef uint8_t		u8;
typedef uint16_t	u16;
typedef uint32_t	u32;
typedef uint64_t	u64;

// signed integers

typedef int8_t		i8;
typedef int16_t		i16;
typedef int32_t		i32;
typedef int64_t		i64;

// floating point

typedef float		f32;
typedef double		f64;

#if sizeof(float) != 4
#error "Warbler is not compatible on this system, 32 bit floats are requred"
#endif

#if sizeof(double) != 8
#error "Warbler is not compatible on this system, 64 bit double are required"
#endif


#endif
