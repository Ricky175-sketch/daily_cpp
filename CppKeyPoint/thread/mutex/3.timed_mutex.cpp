#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::timed_mutex mtx;

void print(const std::string& str)
{
    if (mtx.try_lock_for(std::chrono::seconds(1)))
    {
        std::cout << str << std::endl;
        mtx.unlock();
    }
    else
        std::cout << "Timeout" << std::endl;
}

int main()
{
    std::thread t1(print, "Hello");
    std::thread t2(print, "World");
    t1.join();
    t2.join();

    return 0;
}