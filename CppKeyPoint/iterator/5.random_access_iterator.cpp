#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::vector<int>::iterator iter;

    for (iter = vec.begin(); iter != vec.end(); ++iter)
        std::cout << *iter << " ";
    std::cout << std::endl;

    return 0;
}