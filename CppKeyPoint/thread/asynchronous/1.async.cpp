#include <iostream>
#include <future>
#include <chrono>

int foo(int a, int b)
{
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟耗时操作
    return a + b;
}

int main()
{
    std::future<int> result = std::async(foo, 1, 2); // 启动异步任务
    std::cout << "Wait..." << std::endl;
    std::cout << "Sum = " << result.get() << std::endl; // 获取异步任务结果

    return 0;
}