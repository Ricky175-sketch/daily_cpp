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
