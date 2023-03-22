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

class IDataApiFactory
{
public:
    IDataApiFactory()
    {
        this->_export = nullptr;
        this->_import = nullptr;
    }
    virtual ~IDataApiFactory()
    {
        if (this->_export != nullptr)
        {
            delete this->_export;
            this->_export = nullptr;
        }
        if (this->_import != nullptr)
        {
            delete this->_import;
            this->_import = nullptr;
        }
    }
    bool export(const std::string &data)
    {
        if (this->_export == nullptr)
            this->_export = this->newExport();
        return this->_export->export(data);
    }
    bool import(const std::string &data)
    {
        if (this->_import == nullptr)
            this->_import = this->newImport();
        return this->_import->import(data);
    }
protected:
    virtual IExport *newExport(/* 可以添加自定义参数 */) = 0;
    virtual IImport *newImport(/* 可以添加自定义参数 */) = 0;
private:
    IExport *_export;
    IImport *_import;
};

int main()
{
    return 0;
}