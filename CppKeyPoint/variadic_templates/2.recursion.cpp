#include <iostream>

template<typename T>
void print(const T& value)
{
    std::cout << value << std::endl;
}

template<typename T, typename... Args>
void print(const T& value, const Args&... args)
{
    std::cout << value << std::endl;
    print(args...);
}

int main()
{
    print(1, 2.5, "hello", "world");  // 输出1, 2.5, hello, world

    return 0;
}