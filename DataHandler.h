#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include<memory>
#include<vector>
#include<QString>
#include "Student.h"

class IHandleData{
public:
    virtual ~IHandleData();

    virtual std::vector<std::shared_ptr<Student>> loadFromFile(const QString& fileName) = 0;
    virtual bool saveData(const QString& fileName,std::vector<std::shared_ptr<Student>>& students) = 0;

};

#endif // DATAHANDLER_H
