#ifndef IODATAHANDLER_H
#define IODATAHANDLER_H
#include"../FileChooicer.h"
#include<QTableWidget>
#include"QSettings"
#include<QDateEdit>
#include<QComboBox>
#include<QJsonObject>
#include<QStringListModel>



class ImportSaveData
{
public:
    ~ImportSaveData() = default;
    ImportSaveData() = default;

    void loadFromFile(QTableWidget* table,QWidget* p);
    void SaveToJson(QTableWidget* table,QWidget* p);

    void loadFromRecordBook(QTableWidget* table,QWidget* p);
    void saveToJSonRecordBook(QTableWidget* table,QWidget* p);

    void saveToJsonProject(QTableWidget* table, QWidget* p);
    void loadFromProject(QTableWidget* table,QWidget* p);

    void saveToJsonCourseWork(QTableWidget* table, QWidget* p);
    void loadFromCourseWork(QTableWidget* table, QWidget* p);

    void saveToJsonDiploma(QTableWidget* table, QWidget* p);
    void loadFromDiploma(QTableWidget* table, QWidget* p);

    void SaveDateWidget(QTableWidget* table);

    void loadListInformationPassport(QStringListModel* model,QWidget*p,QJsonObject& obj);
    void loadListInformationExtra(QStringListModel* model,QWidget*p,QJsonObject& obj);

private:
    FileManager fileManager;
};

#endif // IODATAHANDLER_H
