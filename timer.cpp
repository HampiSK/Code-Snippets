#include <iostream>
#include <chrono>

void timer(int milliseconds)
{
   auto start = std::chrono::steady_clock::now();
   while (true)
   {
       auto end = std::chrono::steady_clock::now();

       if (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() > milliseconds)
       break;
   }
}

int main()
{
    std::cout << "I'll be back in 5 seconds." << std::endl;
    timer(5000); // 5 sec = 5000 millisec
    std::cout << "I'm back!" << std::endl;
}
