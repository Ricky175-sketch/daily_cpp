#include <iostream>
#include <functional>

int main()
{
    std::function<void(int, int)> f = [](int a, int b) {
        std::cout << "a = " << a << ", b = " << b << std::endl;
    };
    f(1, 2); // 调用lambda表达式

    return 0;
}