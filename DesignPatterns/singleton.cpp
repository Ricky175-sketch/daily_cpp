// class Singleton
// {
// public:
//     static Singleton *getInstance()
//     {
//         if (_instance == nullptr)
//             _instance = new Singleton();
//         return _instance;
//     }
// private:
//     Singleton() {}
//     ~Singleton() {}
//     Singleton(const Singleton &clone) {} // 禁用拷贝构造
//     Singleton &operator=(const Singleton &s) {} // 禁用赋值
//     static Singleton *_instance;
// };
// Singleton *Singleton::_instance = nullptr;

// #include <cstdlib>
// class Singleton
// {
// public:
//     static Singleton *getInstance()
//     {
//         if (_instance == nullptr)
//         {
//             _instance = new Singleton();
//             atexit(destructor); // 当进程退出时调用destructor，完成堆区内存的释放
//         }
//         return _instance;
//     }
// private:
//     static void destructor()
//     {
//         if (_instance != nullptr)
//         {
//             delete _instance;
//             _instance = nullptr;
//         }
//     }
//     Singleton() {}
//     ~Singleton() {}
//     Singleton(const Singleton &clone) {} // 禁用拷贝构造
//     Singleton &operator=(const Singleton &s) {} // 禁用赋值
//     static Singleton *_instance;
// };
// Singleton *Singleton::_instance = nullptr;

// #include <cstdlib>
// #include <mutex>
// class Singleton
// {
// public:
//     static Singleton *getInstance()
//     {
//         if (_instance == nullptr)
//         {
//             std::lock_guard<std::mutex> lock(_mutex); // 因为全局的_instance只需要初始化一次，故在判断_instance不为空之后再加锁，避免多次加锁，造成性能损失
//             if (_instance == nullptr) // 再次判断_instance不为空，避免多个线程同时到达进行加锁，_instance初始化多次
//             {
//                 _instance = new Singleton();
//                 atexit(destructor); // 当进程退出时调用destructor，完成堆区内存的释放
//             }
//         }
//         return _instance;
//     }
// private:
//     static void destructor()
//     {
//         if (_instance != nullptr)
//         {
//             delete _instance;
//             _instance = nullptr;
//         }
//     }
//     Singleton() {}
//     ~Singleton() {}
//     Singleton(const Singleton &clone) {} // 禁用拷贝构造
//     Singleton &operator=(const Singleton &s) {} // 禁用赋值
//     static Singleton *_instance;
//     static std::mutex _mutex;
// };
// Singleton *Singleton::_instance = nullptr;
// std::mutex Singleton::_mutex; // 初始化互斥锁

#include <cstdlib>
#include <mutex>
#include <atomic>
class Singleton
{
public:
    static Singleton *getInstance()
    {
        Singleton *tmp = _instance.load(std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_acquire); // 获取内存屏障
        if (tmp == nullptr)
        {
            std::lock_guard<std::mutex> lock(_mutex); // 因为全局的_instance只需要初始化一次，故在判断_instance不为空之后再加锁，避免多次加锁，造成性能损失
            tmp = _instance.load(std::memory_order_relaxed);
            if (tmp == nullptr) // 再次判断_instance不为空，避免多个线程同时到达进行加锁，_instance初始化多次
            {
                tmp = new Singleton;
                std::atomic_thread_fence(std::memory_order_release); // 释放内存屏障
                _instance.store(tmp, std::memory_order_relaxed);
                atexit(destructor);
            }
        }
        return tmp;
    }
private:
    static void destructor()
    {
        if (_instance != nullptr)
        {
            delete _instance;
            _instance = nullptr;
        }
    }
    Singleton() {}
    ~Singleton() {}
    Singleton(const Singleton &clone) {} // 禁用拷贝构造
    Singleton &operator=(const Singleton &s) {} // 禁用赋值
    static std::atomic<Singleton*> _instance;
    static std::mutex _mutex;
};
std::atomic<Singleton*> Singleton::_instance;
std::mutex Singleton::_mutex; // 初始化互斥锁