#include "sync_queue.h"
#include <thread>
#include <iostream>
#include <mutex>
using namespace std;

SyncQueue<int> syncQueue(5);

void PutData()
{
    for (int i = 0; i < 20; ++i)
        syncQueue.Put(i);

    std::cout << "PutData finish" << std::endl;
}

void TakeData()
{
    int x = 0;

    for (int i = 0; i < 20; ++i)
    {
        syncQueue.Take(x);
        std::cout << x << std::endl;
    }
    std::cout << "TakeData finish" << std::endl;
}

int main(void)
{
    std::thread t1(PutData);  // �����߳�
    std::thread t2(TakeData); // �����߳�

    t1.join();
    t2.join();

    std::cout << "main finish" << std::endl;
    return 0;
}
