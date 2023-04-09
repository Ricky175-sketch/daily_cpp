#include <iostream>
#include <functional>

int add(int a, int b, int c)
{
    return a + b + c;
}

int main()
{
    auto f = std::bind(add, 1, std::placeholders::_1, 3);
    std::cout << f(2) << std::endl; // 调用add函数

    return 0;
}