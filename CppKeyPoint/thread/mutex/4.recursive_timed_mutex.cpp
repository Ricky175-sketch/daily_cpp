#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::recursive_timed_mutex mtx;

void func(int n)
{
    if (mtx.try_lock_for(std::chrono::seconds(1)))
    {
        std::cout << "Thread " << n << " locked the mutex." << std::endl;
        if (n > 1)
            func(n - 1);
        mtx.unlock();
        std::cout << "Thread " << n << " unlocked the mutex." << std::endl;
    }
    else
    {
        std::cout << "Timeout!" << std::endl;
        return;
    }
}

int main()
{
    std::thread t(func, 5);
    t.join();

    return 0;
}