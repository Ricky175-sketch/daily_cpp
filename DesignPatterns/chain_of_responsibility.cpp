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
    void GetNextHandler(IHandler *next)
    {
        next = this->next;
    }
    bool Handle(const Context &ctx)
    {
        if (this->CanHandle(ctx))
            return this->HandlerRequest(ctx);
        else if (this->GetNextHandler())
            return this->GetNextHandler()->Handle(ctx);
        else
            perror("error");
        return false;
    }
protected:
    virtual bool HandlerRequest(const Context &ctx) = 0;
    virtual bool CanHandle(const Context &ctx) = 0;
    IHandler *GetNextHandler()
    {
        return this->next;
    }
private:
    IHandler *next;
};