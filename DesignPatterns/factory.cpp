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