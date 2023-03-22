#include <iostream>

class Context
{
public:
    bool isMgr;
};

class CalcBonus
{
public:
    CalcBonus(CalcBonus *c = nullptr) : cc(c) {}
    virtual double Calc(Context &ctx)
    {
        return 0.0;
    }
    virtual ~CalcBonus() {}
protected:
    CalcBonus *cc;
};