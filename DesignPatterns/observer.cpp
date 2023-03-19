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

class WeatherData
{

};

class DataCenter
{
public:
    bool attach(IDisplay *ob);
    bool detach(IDisplay *ob);
    void notify()
    {
        float temperature = CalcTemperature();
        for (auto iter = this->obs.begin(); iter != obs.end(); iter++)
            (*iter)->show(temperature);
    }
private:
    virtual WeatherData *GetWeatherData();
    virtual float CalcTemperature()
    {
        WeatherData *data = GetWeatherData();
        // ...
        float temperature;
        return temperature;
    }
    std::vector<IDisplay *> obs;
};

int main()
{
    return 0;
}