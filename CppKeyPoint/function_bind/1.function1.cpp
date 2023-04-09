#include <iostream>
#include <functional>

void foo(int a, int b)
{
    std::cout << "a = " << a << ", b = " << b << std::endl;
}

int main()
{
    std::function<void(int, int)> f = foo;
    f(1, 2); // 调用foo函数

    return 0;
}