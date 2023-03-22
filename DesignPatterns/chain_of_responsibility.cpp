#include <iostream>
#include <string>

class Context
{
public:
    std::string name;
    int day;
};

class IHandler
{
public:
    virtual ~IHandler() {}
    void SetNextHandler(IHandler *next)
    {
        this->next = next;
    }
    bool Handle(const Context &ctx)
    {
        if (this->CanHandle(ctx))
            return this->HandleRequest(ctx);
        else if (this->GetNextHandler())
            return this->GetNextHandler()->Handle(ctx);
        else
            perror("error");
        return false;
    }
protected:
    virtual bool HandleRequest(const Context &ctx) = 0;
    virtual bool CanHandle(const Context &ctx) = 0;
    IHandler *GetNextHandler()
    {
        return this->next;
    }
private:
    IHandler *next;
};

class HandleByMainProgram : public IHandler
{
protected:
    virtual bool HandleRequest(const Context &ctx)
    {
        // 自己的处理逻辑
        std::cout << "Main Program" << std::endl;
        return true;
    }
    virtual bool CanHandle(const Context &ctx)
    {
        if (ctx.day <= 10)
            return true;
        return false;
    }
};

class HandleByProjMgr : public IHandler
{
protected:
    virtual bool HandleRequest(const Context &ctx)
    {
        std::cout << "Project Manager" << std::endl;
        return true;
    }
    virtual bool CanHandle(const Context &ctx)
    {
        if (ctx.day <= 20)
            return true;
        return false;
    }
};

class HandleByBoss : public IHandler
{
protected:
    virtual bool HandleRequest(const Context &ctx)
    {
        std::cout << "Boss" << std::endl;
        return true;
    }
    virtual bool CanHandle(const Context &ctx)
    {
        if (ctx.day < 30)
            return true;
        return false;
    }
};

int main()
{
    IHandler *h1 = new HandleByMainProgram();
    IHandler *h2 = new HandleByProjMgr();
    IHandler *h3 = new HandleByBoss();
    h1->SetNextHandler(h2);
    h2->SetNextHandler(h3);

    Context ctx = Context();
    ctx.day = 15;
    h1->Handle(ctx);

    return 0;
}