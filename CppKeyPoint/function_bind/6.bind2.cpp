#include <iostream>
#include <functional>

class Bar
{
public:
    void foo(int a, int b, int c)
    {
        std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
    }
};

int main()
{
    Bar bar;
    auto f = std::bind(&Bar::foo, &bar, 1, 2, 3);
    f(); // 调用foo函数

    return 0;
}