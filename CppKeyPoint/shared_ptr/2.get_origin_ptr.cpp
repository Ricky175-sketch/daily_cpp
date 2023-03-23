#include <iostream>
#include <memory>

int main()
{
    auto p = std::make_shared<int>(100);
    int *op = p.get();
    // delete op; // forbidden

    return 0;
}