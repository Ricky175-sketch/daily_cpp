#include <iostream>
#include <vector>

using namespace std;

class IDisplay
{
public:
    virtual void show(float temperature) = 0;
    virtual ~IDisplay() {}
};

class DisplayA : public IDisplay
{
public:
    virtual void show(float temperature);

private:
    void ownFunction(); // 可以在子类上继续添加自己需要的函数
};

class DisplayB : public IDisplay
{
public:
    virtual void show(float temperature);
};

class DisplayC : public IDisplay
{
public:
    virtual void show(float temperature);
};

int main()
{
    return 0;
}