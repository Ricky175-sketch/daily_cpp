#include <iostream>
#include <memory>

class A
{
};

int main()
{
    auto p1(std::make_unique<A>());
    std::unique_ptr<A> p2(new A); // 两者是等价的

    return 0;
}