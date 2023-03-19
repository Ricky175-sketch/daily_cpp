#include <iostream>
#include <vector>

using namespace std;

class IDisplay
{
public:
    virtual void show(float temperature) = 0;
    virtual ~IDisplay() {}
};

int main()
{
    return 0;
}