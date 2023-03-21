class Singleton
{
public:
    static Singleton *getInstance()
    {
        if (_instance == nullptr)
            _instance = new Singleton();
        return _instance;
    }
private:
    Singleton() {}
    ~Singleton() {}
    Singleton(const Singleton &clone) {} // 禁用拷贝构造
    Singleton &operator=(const Singleton &s) {} // 禁用赋值
    static Singleton *_instance;
};
Singleton *Singleton::_instance = nullptr;