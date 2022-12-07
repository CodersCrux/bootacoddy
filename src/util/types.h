#ifndef _BOOTACODDY_UTIL_TYPES_HPP
#define _BOOTACODDY_UTIL_TYPES_HPP

#define cname extern "C"

#ifndef asm
#define asm __asm__ volatile
#endif

#ifdef __INT8_TYPE__
typedef __INT8_TYPE__ i8;
typedef __INT8_TYPE__ int8_t;
#endif
#ifdef __INT16_TYPE__
typedef __INT16_TYPE__ i16;
typedef __INT16_TYPE__ int16_t;
#endif
#ifdef __INT32_TYPE__
typedef __INT32_TYPE__ i32;
typedef __INT32_TYPE__ int32_t;
#endif
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ i64;
typedef __INT64_TYPE__ int64_t;
#endif
#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ u8;
typedef __UINT8_TYPE__ uint8_t;
#endif
#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ u16;
typedef __UINT16_TYPE__ uint16_t;
#endif
#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ u32;
typedef __UINT32_TYPE__ uint32_t;
#endif
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ u64;
typedef __UINT64_TYPE__ uint64_t;
#endif

typedef u32 size_t;

struct vec2b { u8 x, y; };
struct vec2w { u16 x, y; };
struct vec2d { u32 x, y; };
struct vec2i { i32 x, y; };
struct vec2f { float x, y; };

#endif