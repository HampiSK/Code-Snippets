#include <iostream>
#include <string>
#include <vector>

/* Simple overloaded print function to print arguments */

constexpr char PRINT_DELIMETER = ' ';

/**
 * @brief Empty print function; flushes stream
 */
inline void print()
{
    std::cout << std::endl;
}

/**
 * @brief Print out passed argument
 */
template <typename T>
inline void print(const T& arg)
{
    std::cout << arg << std::endl;
}

/**
 * @brief Print all elements in vector container
 */
template <typename T>
void print(const std::vector<T>& container)
{
    for (const auto& element : container)
    {
        std::cout << element << PRINT_DELIMETER;
    }
}

/**
 * @brief Print all elements stored in an array. The array is passed as a reference
 *        to the function, keeping the size information
 */
template <typename T, size_t S>
void print(const T(&container)[S])
{
    if (container == nullptr)
    {
        return;
    }

    for (size_t i = 0; i < S; ++i)
    {
        std::cout << container[i] << PRINT_DELIMETER;
    }
}

/**
 * @brief Print all char array as a string; keeping the size information
 */
template <size_t S>
void print(const char(&container)[S])
{
    if (container == nullptr)
    {
        return;
    }

    for (size_t i = 0; i < S; ++i)
    {
        std::cout << container[i];
    }
}

template <typename T>
inline void printFirst(const T& arg)
{
    std::cout << arg << PRINT_DELIMETER;
}

/**
 * @brief Using variadic function to print more arguments recursively
 */
template <typename First, typename... T>
void print(const First& first, const T... args)
{
    printFirst(first);
    print(args...); // Called recursively
}

int main()
{
    print(465465, 4L, -5, "dsadas", 0.1f, 'A');
    print();
    print(50);
    std::vector<int> vec = { 656,46,54,65,4,65,465,4,65,6 };
    print(vec);

    return 0;
}
