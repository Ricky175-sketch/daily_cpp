#include <iostream>

using namespace std;

class Context
{
    // 环境类
};

class ProStrategy
{
    // 抽象的策略类
public:
    // 算法接口
    virtual double CalcPro(const Context &ctx) = 0;
    virtual ~ProStrategy();
};

// 派生出的具体策略类
class VAC_Spring : public ProStrategy {
public:
    virtual double CalcPro(const Context &ctx){}
};

class VAC_Labor : public ProStrategy {
public:
    virtual double CalcPro(const Context &ctx){}
};
class VAC_Labor1  : public VAC_Labor {
public:
    virtual double CalcPro(const Context &ctx){}
};

class VAC_National : public ProStrategy {
public:
    virtual double CalcPro(const Context &ctx){}
};

class VAC_Christmas : public ProStrategy {
public:
    virtual double CalcPro(const Context &ctx){}
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
    Context ctx;
    ProStrategy *s = new VAC_Labor1();
    Promotion *p = new Promotion(s);
    p->CalcPromotion(ctx);
    return 0;
}