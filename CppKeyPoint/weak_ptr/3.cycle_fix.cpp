#include <iostream>
#include <memory>

class A;
class B;

class A
{
public:
    std::weak_ptr<B> bp;
    ~A()
    {
        std::cout << "A destructor" << std::endl;
    }
};

class B
{
public:
    std::shared_ptr<A> ap;
    ~B()
    {
        std::cout << "B destructor" << std::endl;
    }
};

int main()
{
    {
        std::shared_ptr<A> p1(new A);
        std::shared_ptr<B> p2(new B);

        p1->bp = p2;
        p2->ap = p1;
    }

    std::cout << "program end" << std::endl;

    return 0;
}