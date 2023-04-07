#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker()
{
    std::unique_lock<std::mutex> lock(mtx);
    while (!ready)
    {
        cv.wait(lock);
    }
    std::cout << "Worker thread is processing data" << std::endl;
}

int main()
{
    std::thread worker_thread(worker);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::unique_lock<std::mutex> lock(mtx);
        ready = true;
        cv.notify_one();
        std::cout << "main() signals data ready for processing" << std::endl;
    }

    worker_thread.join();

    return 0;
}