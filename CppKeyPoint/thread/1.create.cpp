#include <iostream>
#include <thread>

class A
{
public:
    static void func1(int a)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "param a " << a << std::endl;
    }
};

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

    std::thread t3(&A::func1, 3);
    if (t3.joinable())
    {
        t3.join();
        std::cout << "t2 join" << std::endl;
    }

    return 0;
}