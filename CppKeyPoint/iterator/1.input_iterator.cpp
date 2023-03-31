#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> vec;
    std::istream_iterator<int> input_iter(std::cin);
    std::istream_iterator<int> end_of_input;

    // 从标准输入流中读取整数，并加入到 vector 中
    while (input_iter != end_of_input)
        vec.push_back(*input_iter++);

    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout));
    std::cout << std::endl;

    return 0;
}