#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::queue<int> data;       // 共享数据队列
std::mutex mtx;             // 互斥锁
std::condition_variable cv; // 条件变量
bool ready = false;         // 数据是否准备好的标志

void producer()
{
    for (int i = 0; i < 10; ++i)
    {
        std::unique_lock<std::mutex> lock(mtx); // 获取互斥锁
        data.push(i);                           // 生产数据
        std::cout << "Producer produced " << i << std::endl;
        ready = true;                                                // 标记数据已经准备好
        lock.unlock();                                               // 释放锁
        cv.notify_one();                                             // 通知消费者线程
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 等待一段时间
    }
}

void consumer()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx); // 获取互斥锁
        cv.wait(lock, []
                { return ready; }); // 等待数据准备好的信号
        int value = data.front();   // 取出数据
        data.pop();                 // 移除数据
        std::cout << "Consumer consumed " << value << std::endl;
        ready = false;                                               // 标记数据已经被消费
        lock.unlock();                                               // 释放锁
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 等待一段时间
    }
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.detach();
    t2.detach();

    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}