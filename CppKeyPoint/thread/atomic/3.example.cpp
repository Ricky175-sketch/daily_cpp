#include <iostream> // std::cout
#include <atomic>   // std::atomic, std::memory_order_relaxed
#include <thread>   // std::thread

// std::atomic<int> foo = 0;//错误初始化
std::atomic<int> foo(0); // 准确初始化

void set_foo(int x)
{
    foo.store(x, std::memory_order_relaxed); // set value atomically
}

void print_foo()
{
    int x;
    do
    {
        x = foo.load(std::memory_order_relaxed); // get value atomically
    } while (x == 0);
    std::cout << "foo: " << x << '\n';
}

int main()
{
    std::thread t1(print_foo);
    std::thread t2(set_foo, 10);

    t1.join();
    t2.join();

    std::cout << "main finish\n";

    return 0;
}
