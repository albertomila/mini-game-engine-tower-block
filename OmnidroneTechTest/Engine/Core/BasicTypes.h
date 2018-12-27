#pragma once
#include <stdint.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t ui8;
typedef uint16_t ui16;
typedef uint32_t ui32;
typedef uint64_t ui64;

typedef signed __int8		S8;
typedef signed __int16		S16;
typedef signed __int32		S32;
typedef signed __int64		S64;

typedef unsigned __int8		U8;
typedef unsigned __int16	U16;
typedef unsigned __int32	U32;
typedef unsigned __int64	U64;

template<class T>
inline void Unused(const T&)
{
};