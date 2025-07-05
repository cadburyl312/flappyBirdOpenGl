#include <iostream>
#include <iomanip>
#include <format>
#include "bird.h"
#include <chrono>

unsigned FrameCount = 0;


int main(int argc, char** argv)
{
    const char* bird1 = "first Bird";
    std::cout << "Hello World!\n";

    Bird firstBird(5, 5, 5, bird1);
    std::cout << std::fixed << std::setprecision(2)
              << firstBird.getBirdX() << '\n'
              << firstBird.getBirdY() << '\n'
              << firstBird.getBirdZ() << '\n';

    return 0;
}