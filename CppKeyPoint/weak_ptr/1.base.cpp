#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<int> p(new int(1));
    std::shared_ptr<int> pp = p;
    std::weak_ptr<int> wp(p);
    std::cout << wp.use_count() << std::endl;

    return 0;
}