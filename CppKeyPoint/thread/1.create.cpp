#include <iostream>
#include <thread>

int main()
{
    std::thread t1([]{
        std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
    });
    t1.join();

    std::thread t2([] (int a, int b) {
        std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
        std::cout << "a + b = " << a + b << std::endl;
    }, 1, 2);
    t2.join();

    return 0;
}