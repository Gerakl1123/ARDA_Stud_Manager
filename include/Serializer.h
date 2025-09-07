#ifndef SERIALIZER_H
#define SERIALIZER_H
#include<QWidget>
#include<QTableWidget>
#include<QTableWidgetItem>
#include<QSettings>
#include"../IODataHandler.h"
#include"../ModeSerelization.h"
class LogicOperation;


class SerializerData
{
public:
    SerializerData();

    void DataSerelization(QWidget* w, ModeSerelization mode);
    void DataSerelizationMenuStudentRecords(QTableWidget* t,QWidget* p,ModeSerelization);
    void DataSerelizationCourse(QTableWidget* t,QWidget* p);
    void DataSerelizationDiploma(QTableWidget* t,QWidget* p);
    ~SerializerData();

private:
    std::unique_ptr<ImportSaveData> saveDataManager;
    LogicOperation* logicOperation;
};

#endif // SERIALIZER_H
