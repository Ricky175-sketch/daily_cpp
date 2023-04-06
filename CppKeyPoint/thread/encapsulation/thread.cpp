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
        // �����Դû�б�detach���߱�join�����Լ��ͷ�
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
        _th->join();  // ����detach��ȥjoin
    }
}

void Thread::detach()
{
    _th->detach();
}

size_t Thread::CURRENT_THREADID()
{
    // ����Ϊthread_local�ı��ر������߳����ǳ������ڵģ���ͬ����ͨ��ʱ�������������ڣ�
    // ������static����һ���ĳ�ʼ���������������ڣ���ʹ����������Ϊstatic��
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
        pThread->run(); // ������������
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
