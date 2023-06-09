#include <iostream>
#include <thread>
#include <mutex>

std::once_flag flag1, flag2;

void simple_do_once()
{
    std::cout << "simple_do_once\n";
    std::call_once(flag1, []() {
        std::cout << "Simple example: called once";
    });
}

void may_throw_function(bool do_throw)
{
    if (do_throw)
    {
        std::cout << "throw: call_once will retry" << std::endl;
        throw std::exception();
    }
    std::cout << "Didn't throw, call_once will not attempt again" << std::endl;
}

void do_once(bool do_throw)
{
    try
    {
        std::call_once(flag2, may_throw_function, do_throw);
    }
    catch (...)
    {
    }
}

int main()
{
    std::thread st1(simple_do_once);
    std::thread st2(simple_do_once);
    std::thread st3(simple_do_once);
    std::thread st4(simple_do_once);
    st1.join();
    st2.join();
    st3.join();
    st4.join();

    //    std::thread t1(do_once, false);
    //    std::thread t2(do_once, false);
    //    std::thread t3(do_once, false);
    //    std::thread t4(do_once, true);
    //    t1.join();
    //    t2.join();
    //    t3.join();
    //    t4.join();
}
