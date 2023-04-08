#include <iostream>
#include <future>
#include <chrono>

int foo(int a, int b)
{
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟耗时操作
    return a * b;
}

int main()
{
    std::future<int> result = std::async(std::launch::async, foo, 2, 3); // 启动异步任务
    std::cout << "Wait..." << std::endl;

    while (result.wait_for(std::chrono::milliseconds(200)) != std::future_status::ready)
        std::cout << "." << std::flush;
    std::cout << std::endl;

    int sum = result.get();
    std::cout << "Mul = " << sum << std::endl; // 获取异步任务结果

    return 0;
}