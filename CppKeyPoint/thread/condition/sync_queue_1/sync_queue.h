#pragma once
#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>

template <typename T>
class SyncQueue
{
private:
    bool IsFull() const
    {
        return _queue.size() == _maxSize;
    }

    bool IsEmpty() const
    {
        return _queue.empty();
    }

public:
    SyncQueue(int maxSize) : _maxSize(maxSize)
    {
    }

    void Put(const T &x)
    {
        std::lock_guard<std::mutex> locker(_mutex);

        while (IsFull())
        {
            std::cout << "full wait... size " << _queue.size() << std::endl;
            _notFull.wait(_mutex);
        }

        _queue.push_back(x);
        _notEmpty.notify_one();
    }

    void Take(T &x)
    {
        std::lock_guard<std::mutex> locker(_mutex);

        while (IsEmpty())
        {
            std::cout << "empty wait.." << std::endl;
            _notEmpty.wait(_mutex);
        }

        x = _queue.front();
        _queue.pop_front();
        _notFull.notify_one();
    }

    bool Empty()
    {
        std::lock_guard<std::mutex> locker(_mutex);
        return _queue.empty();
    }

    bool Full()
    {
        std::lock_guard<std::mutex> locker(_mutex);
        return _queue.size() == _maxSize;
    }

    size_t Size()
    {
        std::lock_guard<std::mutex> locker(_mutex);
        return _queue.size();
    }

    int Count()
    {
        return _queue.size();
    }

private:
    std::list<T> _queue;                   // ������
    std::mutex _mutex;                     // �����������������������ʹ��
    std::condition_variable_any _notEmpty; // ��Ϊ�յ���������
    std::condition_variable_any _notFull;  // û��������������
    int _maxSize;                          // ͬ����������size
};