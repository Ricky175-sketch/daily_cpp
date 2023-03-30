#include <iostream>

int main()
{
    int x = 10;
    auto lambda = [y = x + 1]() {
        std::cout << "y = " << y << std::endl;
    };
    lambda();

    return 0;
}