#ifndef THREAD_H
#define THREAD_H
#include <thread>

class Thread
{
public:
    Thread(); // 构造函数
    virtual ~Thread(); // 析构函数
    bool start();
    void stop();
    bool isAlive() const; // 线程是否存活.
    std::thread::id id() { return _th->get_id(); }
    std::thread* getThread() { return _th; }
    void join();  // 等待当前线程结束, 不能在当前线程上调用
    void detach(); //能在当前线程上调用
    static size_t CURRENT_THREADID();
protected:
    static void threadEntry(Thread* pThread); // 静态函数, 线程入口
    virtual void run() = 0; // 运行
protected:
    bool  _running; //是否在运行
    std::thread* _th;
};

#endif // THREAD_H
