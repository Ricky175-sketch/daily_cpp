#include <iostream>
#include <vector>
#include <chrono>

int main()
{
    std::vector<int> vec;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; i++)
        vec.push_back(i);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "push_back duration: " << duration.count() << " microseconds" << std::endl;

    vec.clear();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; i++)
        vec.emplace_back(i);
    end = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "emplace_back duration: " << duration.count() << " microseconds" << std::endl;

    return 0;
}