#include <iostream>
#include <functional>

class Baz
{
public:
    void foo(int a, int b) const
    {
        std::cout << "a = " << a << ", b = " << b << std::endl;
    }
};

int main()
{
    std::function<void(const Baz&, int, int)> f = &Baz::foo;
    Baz baz;
    f(baz, 1, 2); // 调用Baz::foo函数

    return 0;
}