#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> nums = {1, 5, 2, 6, 3, 7, 9, 8};
    int threshold = 5;
    std::cout << "Numbers greater than " << threshold << " are: ";
    std::for_each(nums.begin(), nums.end(), [threshold] (int num) {
        if (num > threshold)
            std::cout << num << " ";
    });
    std::cout << std::endl;

    return 0;
}