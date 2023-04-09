#include <iostream>
#include <functional>

class Baz
{
public:
    void operator()(int a, int b, int c)
    {
        std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
    }
};

int main()
{
    Baz baz;
    auto f = std::bind(baz, 1, 2, 3);
    f(); // 调用operator()函数

    return 0;
}