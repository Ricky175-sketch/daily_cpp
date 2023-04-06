#include <iostream>
#include <thread>
#include <mutex>

std::mutex g_mutex;

void print(const std::string& str)
{
    g_mutex.lock();
    std::cout << str << std::endl;
    g_mutex.unlock();
}

int main()
{
    std::thread t1(print, "hello from thread 1");
    std::thread t2(print, "hello from thread 2");

    t1.join();
    t2.join();
    
    return 0;
}