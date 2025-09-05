#ifndef ACCOUNTINGASSESSMENTS_H
#define ACCOUNTINGASSESSMENTS_H

#include <QWidget>
#include<QSettings>
#include"IODataHandler.h"
#include"Serializer.h"
#include<FileChooicer.h>

class academicrecordwindow;
class MainWindow;

namespace Ui {
class accountingassessments;
}

class accountingassessments : public QWidget
{
    Q_OBJECT

public:
    explicit accountingassessments(MainWindow* mainWindow, QWidget *parent = nullptr);

    ~accountingassessments();


private slots:
    void DeleteRow();
    void Find(const QString& searchName);
    void Back();
    void ClearTabl();
    void Printer();

private:
    void setupConnections();
    Ui::accountingassessments *ui;
    std::unique_ptr<ImportSaveData> obj;
    std::unique_ptr<SerializerData> ser;
    MainWindow* backWindow;
    std::unique_ptr<FileManager> fileManager;
};

#endif // ACCOUNTINGASSESSMENTS_H
