#include <iostream>
#include <chrono>

/* Simple millisecond timer using chrono library
 *
 * Compile with:
 *
 *  g++ -std=c++11 timer.cpp
 */

void timer(int milliseconds)
{
   auto start = std::chrono::steady_clock::now();
   while (true)
   {
       auto end = std::chrono::steady_clock::now();

       if (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() >= milliseconds)
           break;  
   }
}

int main()
{
    std::cout << "I'll be back in 3000 milliseconds." << std::endl;
    timer(3000);
    std::cout << "I'm back!" << std::endl;
}
