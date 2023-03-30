#include <iostream>

class MyClass
{
public:
    auto foo()
    {
        int x = 10;
        auto lambda = [this, x]() {
            // 在Lambda中访问当前对象的成员函数和成员变量
            bar();
            std::cout << "x = " << x << std::endl;
        };
        return lambda;
    }

private:
    void bar() { std::cout << "bar" << std::endl; }
};

int main()
{
    MyClass* mc = new MyClass();
    auto lb = mc->foo();
    lb();

    return 0;
}