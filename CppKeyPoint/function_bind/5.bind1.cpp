#include <iostream>
#include <functional>

void foo(int a, int b, int c)
{
    std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
}

int main()
{
    auto f = std::bind(foo, 1, 2, 3);
    f(); // 调用foo函数

    return 0;
}