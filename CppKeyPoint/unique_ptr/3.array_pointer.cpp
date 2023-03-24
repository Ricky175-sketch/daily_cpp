#include <iostream>
#include <memory>

int main()
{
    std::unique_ptr<int []> p1(new int[10]);
    p1[9] = 9;
    // std::shared_ptr<int []> p2(new int[10]); // error
    std::shared_ptr<int> p2(new int[10]); // correct

    return 0;
}