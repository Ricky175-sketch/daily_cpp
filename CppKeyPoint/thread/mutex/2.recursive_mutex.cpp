#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex mtx;

void func(int n)
{
    mtx.lock();
    std::cout << "Thread " << n << " locked the mutex." << std::endl;
    if (n > 1)
        func(n - 1);
    mtx.unlock();
    std::cout << "Thread " << n << " unlocked the mutex." << std::endl;
}

int main()
{
    std::thread t(func, 3);
    t.join();

    return 0;
}