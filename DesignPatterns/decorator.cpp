// 普通员工有销售奖金，累计奖金，部门经理除此之外还有团队奖金；后面可能会添加环比增长奖金，同时可能产生不同的奖金组合；
// 销售奖金 = 当月销售额 * 4%
// 累计奖金 = 总的回款额 * 0.2%
// 部门奖金 = 团队销售额 * 1%
// 环比奖金 = (当月销售额-上月销售额) * 1%
// 销售后面的参数可能会调整

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

class CalcMonthBonus : public CalcBonus
{
public:
    CalcMonthBonus(CalcBonus *c) : CalcBonus(c)
    {
        std::cout << "compose CalcMonthBonus" << std::endl;
    }
    virtual double Calc(Context &ctx)
    {
        double bonus /*= 计算流程忽略*/;
        return bonus + cc->Calc(ctx);
    }
};

class CalcSumBonus : public CalcBonus
{
public:
    CalcSumBonus(CalcBonus *c) : CalcBonus(c) {}
    virtual double Calc(Context &ctx)
    {
        std::cout << "compose CalcSumBonus" << std::endl;
        double bonus /*= 计算流程忽略*/;
        return bonus + cc->Calc(ctx);
    }
};

class CalcGroupBonus : public CalcBonus
{
public:
    CalcGroupBonus(CalcBonus *c) : CalcBonus(c)
    {
        std::cout << "compose CalcGroupBonus" << std::endl;
    }
    virtual double Calc(Context &ctx)
    {
        double bonus /*= 计算流程忽略*/;
        return bonus + cc->Calc(ctx);
    }
};

class CalcCycleBonus : public CalcBonus
{
public:
    CalcCycleBonus(CalcBonus *c) : CalcBonus(c)
    {
        std::cout << "compose CalcCycleBonus" << std::endl;
    }
    virtual double Calc(Context &ctx)
    {
        double bonus /*= 计算流程忽略*/;
        return bonus + cc->Calc(ctx);
    }
};

int main()
{
    Context ctx1;
    CalcBonus *base1 = new CalcBonus();
    CalcMonthBonus *mb = new CalcMonthBonus(base1);
    CalcCycleBonus *cb = new CalcCycleBonus(mb);
    cb->Calc(ctx1);
    CalcSumBonus *sb = new CalcSumBonus(cb);
    sb->Calc(ctx1);

    Context ctx2;
    CalcBonus *base2;
    CalcGroupBonus *gb = new CalcGroupBonus(base2);
    gb->Calc(ctx2);

    return 0;
}