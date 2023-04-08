#include <iostream>
#include <thread>
#include <mutex>

std::once_flag flag;

void init()
{
    std::cout << "Initializing resource" << std::endl;
}

void use_resource()
{
    std::call_once(flag, init);
    std::cout << "Using resource" << std::endl;
}

int main()
{
    std::thread t1([]() {
        use_resource();
    });

    std::thread t2([]() {
        use_resource();
    });

    t1.join();
    t2.join();

    return 0;
}