#include <iostream>
#include <string>

class IExport
{
public:
    virtual bool export(const std::string &data) = 0;
    virtual ~IExport() {}
};

class ExportXml : public IExport
{
public:
    virtual bool export(const std::string &data)
    {
        return true;
    }
};

class ExportJson : public IExport
{
public:
    virtual bool export(const std::string &data)
    {
        return true;
    }
};

class ExportTxt : public IExport
{
public:
    virtual bool export(const std::string &data)
    {
        return true;
    }
};

class ExportCSV : public IExport
{
public:
    virtual bool export(const std::string &data)
    {
        return true;
    }
};

class IImport
{
public:
    virtual bool import(const std::string &data) = 0;
    virtual ~IImport() {}
};

class ImportXml : public IImport
{
public:
    virtual bool import(const std::string &data)
    {
        return true;
    }
};

class ImportJson : public IImport
{
public:
    virtual bool import(const std::string &data)
    {
        return true;
    }
};

class ImportTxt : public IImport
{
public:
    virtual bool import(const std::string &data)
    {
        return true;
    }
};

class ImportCSV : public IImport
{
public:
    virtual bool import(const std::string &data)
    {
        return true;
    }
};

int main()
{
    return 0;
}