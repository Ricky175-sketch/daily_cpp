#include <iostream>

template<typename... Args>
void print(const Args&... args)
{
    ((std::cout << args << '\n'), ...);
}

int main()
{
    print(1, 2.5, "hello", "world");  // 输出12.5helloworld

    return 0;
}