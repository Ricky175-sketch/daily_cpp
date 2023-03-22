#include <iostream>
#include <string>

class IExport
{
public:
    virtual bool Export(const std::string &data) = 0;
    virtual ~IExport() {}
};

class ExportXml : public IExport
{
public:
    virtual bool Export(const std::string &data)
    {
        return true;
    }
};

class ExportJson : public IExport
{
public:
    virtual bool Export(const std::string &data)
    {
        return true;
    }
};

class ExportTxt : public IExport
{
public:
    virtual bool Export(const std::string &data)
    {
        return true;
    }
};

class ExportCSV : public IExport
{
public:
    virtual bool Export(const std::string &data)
    {
        return true;
    }
};

class IImport
{
public:
    virtual bool Import(const std::string &data) = 0;
    virtual ~IImport() {}
};

class ImportXml : public IImport
{
public:
    virtual bool Import(const std::string &data)
    {
        return true;
    }
};

class ImportJson : public IImport
{
public:
    virtual bool Import(const std::string &data)
    {
        return true;
    }
};

class ImportTxt : public IImport
{
public:
    virtual bool Import(const std::string &data)
    {
        return true;
    }
};

class ImportCSV : public IImport
{
public:
    virtual bool Import(const std::string &data)
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
    bool Export(const std::string &data)
    {
        if (this->_export == nullptr)
            this->_export = this->newExport();
        return this->_export->Export(data);
    }
    bool Import(const std::string &data)
    {
        if (this->_import == nullptr)
            this->_import = this->newImport();
        return this->_import->Import(data);
    }

protected:
    virtual IExport *newExport(/* 可以添加自定义参数 */) = 0;
    virtual IImport *newImport(/* 可以添加自定义参数 */) = 0;

private:
    IExport *_export;
    IImport *_import;
};

class XmlApiFactory : public IDataApiFactory
{
protected:
    virtual IExport *newExport(/* ... */)
    {
        // 可能有其它操作，或者许多参数
        IExport *temp = new ExportXml();
        // 可能之后有什么操作
        return temp;
    }
    virtual IImport *newImport(/* ... */)
    {
        // 可能有其它操作，或者许多参数
        IImport *temp = new ImportXml();
        // 可能之后有什么操作
        return temp;
    }
};

class JsonApiFactory : public IDataApiFactory
{
protected:
    virtual IExport *newExport(/* ... */)
    {
        // 可能有其它操作，或者许多参数
        IExport *temp = new ExportJson();
        // 可能之后有什么操作
        return temp;
    }
    virtual IImport *newImport(/* ... */)
    {
        // 可能有其它操作，或者许多参数
        IImport *temp = new ImportJson();
        // 可能之后有什么操作
        return temp;
    }
};
class TxtApiFactory : public IDataApiFactory
{
protected:
    virtual IExport *newExport(/* ... */)
    {
        // 可能有其它操作，或者许多参数
        IExport *temp = new ExportTxt();
        // 可能之后有什么操作
        return temp;
    }
    virtual IImport *newImport(/* ... */)
    {
        // 可能有其它操作，或者许多参数
        IImport *temp = new ImportTxt();
        // 可能之后有什么操作
        return temp;
    }
};

class CSVApiFactory : public IDataApiFactory
{
protected:
    virtual IExport *newExport(/* ... */)
    {
        // 可能有其它操作，或者许多参数
        IExport *temp = new ExportCSV();
        // 可能之后有什么操作
        return temp;
    }
    virtual IImport *newImport(/* ... */)
    {
        // 可能有其它操作，或者许多参数
        IImport *temp = new ImportCSV();
        // 可能之后有什么操作
        return temp;
    }
};

int main()
{
    IDataApiFactory *factory = new CSVApiFactory();
    factory->Import("hello");
    factory->Export("hello");

    return 0;
}