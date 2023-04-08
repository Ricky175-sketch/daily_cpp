#include <iostream>
#include <thread>
#include <future>
#include <chrono>

int foo(int a, int b)
{
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟耗时操作
    return a - b;
}

int main()
{
    std::packaged_task<int(int, int)> task(foo); // 将foo函数包装成可调用对象
    std::future<int> result = task.get_future(); // 获取与task关联的future对象
    std::thread t(std::move(task), 2, 1); // 在另一个线程中执行task函数

    std::cout << "Wait..." << std::endl;
    std::cout << "Sub = " << result.get() << std::endl; // 获取异步任务结果
    t.join();

    return 0;
}