#include <iostream>
#include <memory>

int main()
{
    // std::shared_ptr<int> p1(new int(1));
    // std::shared_ptr<int> p2 = p1;
    // std::shared_ptr<int> p3;
    // p3.reset(new int(1)); // reset括号内有值表示接管新对象，也就是给指针赋值，若无值，则表示释放该指针所拥有的对象

    // std::cout << p1.use_count() << std::endl;
    // std::cout << p3.use_count() << std::endl;

    std::shared_ptr<int> p1(new int(1));
    std::shared_ptr<int> p2 = p1;
    std::cout << "origin" << std::endl;
    std::cout << "p1 use count: " << p1.use_count() << std::endl;
    std::cout << "p2 use count: " << p2.use_count() << std::endl;

    p1.reset();
    std::cout << "\np1 reset" << std::endl;
    std::cout << "p1 use count: " << p1.use_count() << std::endl;
    std::cout << "p2 use count: " << p2.use_count() << std::endl;
    if (!p1)
        std::cout << "p1 is empty" << std::endl;
    if (!p2)
        std::cout << "p2 is empty" << std::endl;

    p2.reset();
    std::cout << "\np2 reset" << std::endl;
    std::cout << "p1 use count: " << p1.use_count() << std::endl;
    std::cout << "p2 use count: " << p2.use_count() << std::endl;
    if (!p1)
        std::cout << "p1 is empty" << std::endl;
    if (!p2)
        std::cout << "p2 is empty" << std::endl;

    return 0;
}