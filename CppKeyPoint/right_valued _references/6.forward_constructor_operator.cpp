#include <iostream>
using namespace std;

class MyClass
{
public:
    MyClass() : m_data(nullptr) {}
    ~MyClass()
    {
        delete[] m_data;
    }
    MyClass(MyClass &&other) noexcept
    {
        cout << "Moving MyClass" << endl;
        m_data = other.m_data;
        other.m_data = nullptr;
    }

    MyClass &operator=(MyClass &&other) noexcept
    {
        cout << "Moving Operator=" << endl;
        if (this != &other)
        {
            delete m_data;
            m_data = other.m_data;
            other.m_data = nullptr;
        }
        return *this;
    }

private:
    int *m_data;
};

int main()
{
    MyClass t1;
    MyClass t2;

    MyClass t3(forward<MyClass>(t1));
    MyClass t4 = forward<MyClass>(t2);

    return 0;
}