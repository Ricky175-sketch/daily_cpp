#include <iostream>

using namespace std;

class Context
{

};

class ProStrategy
{
public:
    virtual double CalcPro(const Context &ctx) = 0;
    virtual ~ProStrategy();
};

int main()
{

}