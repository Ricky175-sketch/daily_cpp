#include <iostream>
#include <string>

class IExport
{
public:
    virtual bool export(const std::string &data) = 0;
    virtual ~IExport() {}
};

