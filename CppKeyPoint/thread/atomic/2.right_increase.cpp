#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> counter(0);

void increment()
{
    counter++;
}

int main()
{
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << counter.load() << std::endl;

    return 0;
}