#pragma once

/**
* Helpers used as "internal linkage"
*/
namespace details
{
    constexpr char PRINT_DELIMETER = ' ';

    template <typename T>
    inline void printFirst(const T& arg)
    {
        std::cout << arg << PRINT_DELIMETER;
    }
}