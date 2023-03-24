#include <iostream>
#include <memory>

std::weak_ptr<int> gw;

void f()
{
    if (gw.expired())
        std::cout << "gw has expired" << std::endl;
    else
    {
        auto sp = gw.lock();
        std::cout << *sp << std::endl;
    }
}

int main()
{
    {
        auto sp = std::make_shared<int>(10);
        gw = sp;
        f();
    }
    f(); // sp已经被释放

    return 0;
}