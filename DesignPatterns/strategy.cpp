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

class Promotion
{
public:
    Promotion(ProStrategy *s) : s(s){}
    ~Promotion(){}
    double CalcPromotion(const Context &ctx) {
        return s->CalcPro(ctx);
    }
private:
    ProStrategy *s;
};

int main()
{

}