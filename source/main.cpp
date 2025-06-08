#include <iostream>
#include <iomanip> 
#include <format>
#include "bird.h"

int main()
{
    const char* bird1 = "first Bird";
    std::cout << "Hello World!\n";
    Bird firstBird = Bird(5, 5, 5, bird1);
    std::cout << std::fixed << std::setprecision(2) << firstBird.getBirdX() << '\n';  
    std::cout << std::fixed << std::setprecision(2) << firstBird.getBirdY() << '\n';  
    std::cout << std::fixed << std::setprecision(2) << firstBird.getBirdZ() << '\n';  
}