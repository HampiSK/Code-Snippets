////#include "print.hpp"
//
//constexpr char DELIMETER = ' ';
//
//// Helpers accessed only by internal linkage
//namespace
//{
//    template <typename T>
//    inline void printFirst(const T& arg)
//    {
//        std::cout << arg << DELIMETER;
//    }
//}
//
//inline void print()
//{
//    std::cout << std::endl;
//}
//
//template <typename T>
//inline void print(const T& arg)
//{
//    std::cout << arg << std::endl;
//}
//
///**
// * @brief Print all elements in vector container
// */
//template <typename T>
//void print(const std::vector<T>& container)
//{
//    for (const auto& element : container)
//    {
//        std::cout << element << DELIMETER;
//    }
//}
//
///**
// * @brief Print all elements stored in an array. The array is passed as a reference to the function,
// *        keeping the size information
// */
//template <typename T, size_t S>
//void print(const T(&container)[S])
//{
//    if (container == nullptr)
//    {
//        return;
//    }
//
//    for (size_t i = 0; i < S; ++i)
//    {
//        std::cout << container[i] << DELIMETER;
//    }
//}
//
///**
// * @brief Using variadic function to print more arguments recursively
// */
//template <typename First, typename... T>
//void print(const First& first, const T... args)
//{
//    printFirst(first);
//    print(args...); // Called recursively
//}