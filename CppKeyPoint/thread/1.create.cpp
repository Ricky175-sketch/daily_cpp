#include <iostream>
#include <thread>

int main()
{
    std::thread t1([]{
        std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
    });
    t1.join();



    return 0;
}