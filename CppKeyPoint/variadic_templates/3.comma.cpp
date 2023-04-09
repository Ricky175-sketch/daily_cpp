#include <iostream>

template<typename... Args>
void print(const Args&... args)
{
    int dummy[] = {(std::cout << args << std::endl, 0)...};
}

int main()
{
    print(1, 2.5, "hello", "world");  // 输出1, 2.5, hello, world

    return 0;
}