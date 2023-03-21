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

#include <cstdlib>
class Singleton
{
public:
    static Singleton *getInstance()
    {
        if (_instance == nullptr)
        {
            _instance = new Singleton();
            atexit(destructor); // 当进程退出时调用destructor，完成堆区内存的释放
        }
        return _instance;
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
    static Singleton *_instance;
};
Singleton *Singleton::_instance = nullptr;