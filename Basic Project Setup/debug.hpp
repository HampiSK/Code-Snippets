#pragma once

#include "main.hpp"

#define DEBUG_MODE 1

#if defined(DEBUG_MODE) && DEBUG_MODE == 1
    #define DEBUG_PRINT(...) print(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...) /* Don't do anything in release builds */
#endif
