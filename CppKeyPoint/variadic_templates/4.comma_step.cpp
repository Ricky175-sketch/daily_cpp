#include <iostream>

template<typename F, typename... Args>
void print(const F& f, Args&&... args)
{
    std::initializer_list<int> {(f(std::forward<Args>(args)), 0)...}; // 这里使用了完美转发
}

int main()
{
    print([](int i){std::cout << i << std::endl;}, 1, 2, 3);  // 因为initializer_list为int类型，故这里这里只能传入int类型的参数

    return 0;
}