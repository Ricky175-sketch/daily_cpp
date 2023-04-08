#include <iostream>
#include <thread>
#include <future>
#include <chrono>

void foo(std::promise<int>& p)
{
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟耗时操作
    p.set_value(10);
}

int main()
{
    std::promise<int> p; // 创建一个promise对象
    std::future<int> f = p.get_future(); // 获取与promise关联的future对象
    std::thread t(foo, std::ref(p)); // 在另一个线程中执行foo函数

    std::cout << "Wait..." << std::endl;
    std::cout << "Result = " << f.get() << std::endl; // 获取异步任务结果
    t.join();

    return 0;
}