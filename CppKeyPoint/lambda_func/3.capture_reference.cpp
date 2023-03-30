#include <iostream>

int main()
{
    int x = 10;
    auto lambda = [&x]() {
        x = 20;
        std::cout << "x = " << x << std::endl;
    };
    lambda();
    std::cout << "x = " << x << std::endl;

    return 0;
}