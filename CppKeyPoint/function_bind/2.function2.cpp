#include <iostream>
#include <functional>

class Bar
{
public:
    void operator()(int a, int b)
    {
        std::cout << "a = " << a << ", b = " << b << std::endl;
    }
};

int main()
{
    std::function<void(int, int)> f = Bar();
    f(1, 2); // 调用Bar::operator()函数

    return 0;
}