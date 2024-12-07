#pragma once
#include <cassert>

#define IDN_UNUSED(x) ((void)x)

#if defined(__GNUC__) || defined(__clang__)
#   define IDN_UNREACHABLE() __builtin_unreachable()
#elif defined(_MSC_VER)
#   define IDN_UNREACHABLE()  __assume(0)
#else
#   define IDN_UNREACHABLE() std::abort()
#endif

#if defined (__GNUC__) || defined(__clang__)
#   define IDN_FORCEINLINE  inline __attribute__((always_inline))
#elif defined(_MSC_VER)
#   define IDN_FORCEINLINE  __forceinline
#else
#   define IDN_FORCEINLINE  inline
#endif
