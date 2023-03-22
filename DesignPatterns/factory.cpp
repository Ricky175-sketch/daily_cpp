#include <iostream>
#include <string>

class IExport
{
public:
    virtual bool export(const std::string &data) = 0;
    virtual ~IExport() {}
};

class ExportXml : public IExport {
public:
    virtual bool export(const std::string &data) {
        return true;
    }
};

class ExportJson : public IExport {
public:
    virtual bool export(const std::string &data) {
        return true;
    }
};

class ExportTxt : public IExport {
public:
    virtual bool export(const std::string &data) {
        return true;
    }
};

class ExportCSV : public IExport {
public:
    virtual bool export(const std::string &data) {
        return true;
    }
};

class IExportFactory
{
public:
    IExportFactory()
    {
        this->_export = nullptr;
    }
    virtual ~IExportFactory()
    {
        if (this->_export)
        {
            delete this->_export;
            this->_export = nullptr;
        }
    }
    bool export(const std::string &data)
    {
        if (this->_export == nullptr)
            this->_export = NewExport();
        return this->_export->export(data);
    }
protected:
    virtual IExport *NewExport(/* ... */) = 0;
private:
    IExport *_export;
};

class ExportXmlFactory : public IExportFactory {
protected:
    virtual IExport * NewExport(/* ... */) {
        // 可能有其它操作，或者许多参数
        IExport * temp = new ExportXml();
        // 可能之后有什么操作
        return temp;
    }
};
class ExportJsonFactory : public IExportFactory {
protected:
    virtual IExport * NewExport(/* ... */) {
        // 可能有其它操作，或者许多参数
        IExport * temp = new ExportJson();
        // 可能之后有什么操作
        return temp;
    }
};
class ExportTxtFactory : public IExportFactory {
protected:
    IExport * NewExport(/* ... */) {
        // 可能有其它操作，或者许多参数
        IExport * temp = new ExportTxt();
        // 可能之后有什么操作
        return temp;
    }
};

class ExportCSVFactory : public IExportFactory {
protected:
    virtual IExport * NewExport(/* ... */) {
        // 可能有其它操作，或者许多参数
        IExport * temp = new ExportCSV();
        // 可能之后有什么操作
        return temp;
    }
};

int main()
{
    IExportFactory *factory = new ExportTxtFactory();
    factory->export("hello");

    return 0;
}