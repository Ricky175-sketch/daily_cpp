#include <iostream>
#include <memory>

struct MyDelete
{
    void operator()(int *p)
    {
        std::cout << "delete" << std::endl;
        delete p;
    }
};


int main()
{
    std::unique_ptr<int, void (*)(int *)> p(new int(1), [](int *p) {
        delete p;
    });

    std::unique_ptr<int, MyDelete> p2(new int(1)); // 这里不能使用make_unique进行构造

    return 0;
}