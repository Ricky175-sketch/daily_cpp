#include <iostream>
#include <iterator>
#include <set>

int main()
{
    std::set<int> s{3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::set<int>::iterator iter;
    for (iter = s.begin(); iter != s.end(); ++iter)
        std::cout << *iter << " ";
    std::cout << std::endl;

    return 0;
}