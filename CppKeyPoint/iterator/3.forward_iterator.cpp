#include <iostream>
#include <iterator>
#include <list>

int main()
{
    std::list<int> lst{1, 2, 3, 4, 5};
    std::list<int>::iterator iter = lst.end();

    while (iter != lst.begin())
        std::cout << *--iter << " ";
    std::cout << std::endl;

    return 0;
}