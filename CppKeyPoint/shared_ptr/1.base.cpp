#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<int> p1(new int(1));
    std::shared_ptr<int> p2 = p1;
    std::shared_ptr<int> p3;
    p3.reset(new int(1)); // reset括号内有值表示接管新对象，也就是给指针赋值，若无值，则表示释放该指针所拥有的对象

    std::cout << p1.use_count() << std::endl;
    std::cout << p3.use_count() << std::endl;

    return 0;
}