#include "thread.h"
#include <sstream>
#include <iostream>
#include <exception>
Thread::Thread() :
    _running(false), _th(NULL)
{

}

Thread::~Thread()
{
    if (_th != NULL)
    {
        // 如果资源没有被detach或者被join，则自己释放
        if (_th->joinable())
        {
            _th->detach();
        }

        delete _th;
        _th = NULL;
    }
    std::cout << "~Thread()" << std::endl;
}

bool Thread::start()
{
    if (_running)
    {
        return false;
    }
    try
    {
        _th = new std::thread(&Thread::threadEntry, this);
    }
    catch (...)
    {
        throw  "[Thread::start] thread start error";
    }
    return true;
}

void Thread::stop()
{
    _running = false;
}

bool Thread::isAlive() const
{
    return _running;
}

void Thread::join()
{
    if (_th->joinable())
    {
        _th->join();  // 不是detach才去join
    }
}

void Thread::detach()
{
    _th->detach();
}

size_t Thread::CURRENT_THREADID()
{
    // 声明为thread_local的本地变量在线程中是持续存在的，不同于普通临时变量的生命周期，
    // 它具有static变量一样的初始化特征和生命周期，即使它不被声明为static。
    static thread_local size_t threadId = 0;
    if (threadId == 0)
    {
        std::stringstream ss;
        ss << std::this_thread::get_id();
        threadId = strtol(ss.str().c_str(), NULL, 0);
    }
    return threadId;
}

void Thread::threadEntry(Thread* pThread)
{
    pThread->_running = true;

    try
    {
        pThread->run(); // 函数运行所在
    }
    catch (std::exception& ex)
    {
        pThread->_running = false;
        throw ex;
    }
    catch (...)
    {
        pThread->_running = false;
        throw;
    }
    pThread->_running = false;
}
