#pragma once
#include <cassert>

#define IDN_UNUSED(x) ((void)x)

#if defined(__GNUC__) || defined(__clang__)
#   define IDN_UNREACHEBLE() __builtin_unreachable()
#else
#   define IDN_UNREACHEBLE() assert(false);
#endif
