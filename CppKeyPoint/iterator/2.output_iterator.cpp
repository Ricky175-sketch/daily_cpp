#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::ostream_iterator<int> output_iter(std::cout, " ");

    std::copy(vec.begin(), vec.end(), output_iter);
    std::cout << std::endl;

    return 0;
}