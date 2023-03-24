#include <iostream>
#include <memory>

int main()
{
    std::unique_ptr<int> p1(new int);
    // std::unique_ptr<int> p2 = p1; // error
    std::unique_ptr<int> p2 = std::move(p1);
    if (p1 == nullptr)
        std::cout << "p1 is null" << std::endl;
    if (p2 == nullptr)
        std::cout << "p2 is null" << std::endl;

    return 0;
}