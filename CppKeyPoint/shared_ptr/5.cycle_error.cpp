#include <iostream>
#include <memory>

class A;
class B;

class A
{
public:
    std::shared_ptr<B> bp;
    ~A()
    {
        std::cout << "A destructor" << std::endl; // 释放成员变量的操作在析构函数之后
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
    std::shared_ptr<A> pp;
    {
        std::shared_ptr<A> p1(new A);
        std::shared_ptr<B> p2(new B);

        p1->bp = p2;
        p2->ap = p1;

        pp = p1;
        p2->ap.reset(); // 需要手动释放才行
    }

    std::cout << pp.use_count() << std::endl; // 循环引用导致p1、p2退出了作用域后都没有发生析构

    return 0;
}
