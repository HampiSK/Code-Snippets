#include <iostream>
#include <string>
#include <vector>

/* Simple overloaded print function to print arguments */



/* Non template function to call with zero arguments */
inline void print() {
    std::cout<<std::endl;
}

/* Template function with 1 argument */
template <typename T>
inline void print(const T & arg) {
    std::cout << arg << std::endl;
}

/* Base template used to print all values */
template <typename T>
void printAll(const T & arg) {
    std::cout << arg << " "; // We are not flushing as another values will be printed
}

/* Using recursion, all arguments will be printed */
template <typename First, typename... T>
void printAll(const First & first, const T... args) {
    printAll(first);    
    printAll(args...); // Called multiple times based on args count
}

/* Variadic template with one or more arguments */
template <typename First, typename... T>
void print(const First & first, const T... args) {
    printAll(first);    
    printAll(args...); // Called multiple times based on args count
    
    std::cout<<std::endl; // Flush at the end
}

/* Print all elements in container */
template <typename T>
void print(const std::vector<T> & container) 
{
    for(auto i = container.begin(); i != container.end(); ++i)
        std::cout<<*i<<' ';
    std::cout<<std::endl; // Flush at the end
}

int main()
{
    print(__PRETTY_FUNCTION__); 
    print(465465,4L,-5,"dsadas",0.1f,'A');
    print();
    print(50);
    std::vector<int> vec = {656,46,54,65,4,65,465,4,65,6};
    print(vec);
    
    return 0;
}
