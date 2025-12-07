#ifndef SERIALIZER_H
#define SERIALIZER_H
#include<QWidget>
#include<QTableWidget>
#include<QTableWidgetItem>
#include<QSettings>
#include"IOCore/IODataHandler.h"
#include"ModeSerelization.h"

class LogicOperation;
class SettingsBinder;

class SerializerData : public QObject
{
    Q_OBJECT
public:
    SerializerData() = default;
    explicit SerializerData(QObject* parent);

    void DataSerelization(QWidget* w, ModeSerelization mode);
    void DataSerelizationMenuStudentRecords(QTableWidget* t,QWidget* p,ModeSerelization);
    void DataSerelizationCourse(QTableWidget* t,QWidget* p);
    void DataSerelizationDiploma(QTableWidget* t,QWidget* p);
    ~SerializerData() override;

private:
    std::unique_ptr<ImportSaveData> saveDataManager;
    SettingsBinder* binder;
    std::unique_ptr<LogicOperation> logicOperation;
};

#endif // SERIALIZER_H
