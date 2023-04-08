#include <iostream>
#include <thread>
#include <future>
#include <chrono>

void foo(std::promise<int> &p)
{
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟耗时操作
    p.set_value(10);
}

int main()
{
    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::thread t(foo, std::ref(p));

    std::cout << "Wait..." << std::endl;
    std::cout << "Sum = " << f.get() << std::endl; // 获取异步任务结果
    t.join();

    return 0;
}