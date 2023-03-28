#include <iostream>
#include <string>

template<typename... Args>
void bar(Args&&... args)
{
    std::cout << "this is bar function" << std::endl;
}

template<typename... Args>
void foo(Args&&... args)
{
    bar(std::forward<Args>(args)...);
}

int main()
{
    int x = 42;
    std::string s = "hello";
    foo(x, s);

    return 0;
}