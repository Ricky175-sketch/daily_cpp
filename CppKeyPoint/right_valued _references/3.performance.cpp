#include <iostream>
#include <memory>
#include <cstring>

class MyString
{
public:
    MyString() : str(nullptr) {}
    MyString(const char *s)
    {
        std::cout << "Constructing MyString" << std::endl;
        str = new char[std::strlen(s) + 1];
        std::strcpy(str, s);
    }
    MyString(const MyString &other)
    {
        std::cout << "Copying MyString" << std::endl;
        str = new char[std::strlen(other.str) + 1];
        std::strcpy(str, other.str);
    }
    MyString(MyString &&other) noexcept
    {
        std::cout << "Moving MyString" << std::endl;
        str = other.str;
        other.str = nullptr;
    }
    ~MyString()
    {
        delete[] str;
    }

private:
    char *str;
};

int main()
{
    MyString s1("hello");
    MyString s2(std::move(s1)); // 移动构造函数被调用，避免了深拷贝

    return 0;
}