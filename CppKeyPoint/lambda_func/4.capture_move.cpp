#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v{1, 2, 3};
    auto lambda = [v = std::move(v)]()
    {
        // 对v进行移动操作
        std::cout << "v.size() = " << v.size() << std::endl;
    };
    lambda();

    return 0;
}