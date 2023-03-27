#include <iostream>
#include <vector>

// 定义一个简单的类，包含一个动态分配的数组
class MyClass
{
public:
    MyClass() : data(nullptr), size(0) {}
    MyClass(int n) : data(new int[n]), size(n)
    {
        std::cout << "Constructing MyClass of size " << size << std::endl;
    }
    ~MyClass()
    {
        delete[] data;
        std::cout << "Destructing MyClass of size " << size << std::endl;
    }

    // 移动构造函数，实现移动语义
    MyClass(MyClass &&other) : data(other.data), size(other.size)
    {
        other.data = nullptr;
        other.size = 0;
        std::cout << "Moving MyClass of size " << size << std::endl;
    }

    // 移动赋值运算符，实现移动语义
    MyClass &operator=(MyClass &&other)
    {
        if (this != &other)
        {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            std::cout << "Moving MyClass of size " << size << std::endl;
        }
        return *this;
    }

private:
    int *data;
    int size;
};

int main()
{
    std::vector<MyClass> vec;
    vec.reserve(10);

    // 向vector中添加10个MyClass对象
    for (int i = 0; i < 10; i++)
        vec.emplace_back(i + 1);

    std::cout << "Resizing vector\n";

    // 将vector的大小减半
    vec.resize(5);

    std::cout << "Done\n";

    return 0;
}