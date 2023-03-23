#include <iostream>
#include <memory>

void Destructor(int *p)
{
    std::cout << "call destructor function" << std::endl;
    delete p;
}

int main()
{
    std::shared_ptr<int> p1(new int(10), Destructor);

    std::shared_ptr<int> p2(new int(100), [](int *p) {
        std::cout << "cal lambda destructor function" << std::endl;
        delete p;
    });

    std::shared_ptr<int> ap(new int[10], [](int *p) {
        std::cout << "delete array pointer" << std::endl;
        delete []p;
    });

    return 0;
}