#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "thread_pool.h"

// 矩阵相乘的函数
void multiply(const std::vector<std::vector<int>> &A, const std::vector<std::vector<int>> &B, std::vector<std::vector<int>> &C, size_t row)
{
    size_t num_columns = B[0].size();
    size_t num_inner = A[0].size();

    for (size_t col = 0; col < num_columns; ++col)
    {
        C[row][col] = 0;
        for (size_t inner = 0; inner < num_inner; ++inner)
        {
            C[row][col] += A[row][inner] * B[inner][col];
        }
    }
}

int main()
{
    const size_t matrix_size = 1000;
    std::vector<std::vector<int>> A(matrix_size, std::vector<int>(matrix_size));
    std::vector<std::vector<int>> B(matrix_size, std::vector<int>(matrix_size));
    std::vector<std::vector<int>> C(matrix_size, std::vector<int>(matrix_size));

    // 随机填充矩阵 A 和 B
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);

    for (size_t i = 0; i < matrix_size; ++i)
    {
        for (size_t j = 0; j < matrix_size; ++j)
        {
            A[i][j] = dis(gen);
            B[i][j] = dis(gen);
        }
    }

    // 使用线程池进行矩阵相乘
    ThreadPool pool(4);
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::future<void>> results;
    for (size_t i = 0; i < matrix_size; ++i)
    {
        results.emplace_back(pool.enqueue(multiply, std::cref(A), std::cref(B), std::ref(C), i));
    }

    for (auto &&result : results)
    {
        result.get();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Time elapsed: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
