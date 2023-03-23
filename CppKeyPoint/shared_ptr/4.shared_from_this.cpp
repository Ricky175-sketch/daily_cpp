#include <iostream>
#include <memory>

class A : public std::enable_shared_from_this<A>
{
public:
    std::shared_ptr<A> getSelf()
    {
        return shared_from_this();
    }
    ~A()
    {
        std::cout << "destructor" << std::endl;
    }
};

int main()
{
    auto p1 = std::make_shared<A>();
    std::shared_ptr<A> p2 = p1->getSelf();

    return 0;
}