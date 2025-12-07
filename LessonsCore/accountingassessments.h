#ifndef ACCOUNTINGASSESSMENTS_H
#define ACCOUNTINGASSESSMENTS_H

#include <QWidget>
#include<QSettings>
#include"../IOCore/IODataHandler.h"
#include"../Serializer.h"
#include"../FileChooicer.h"
#include<QComboBox>
#include"../IOCore/iodatabasehandler.h"
#include"../tablemanager.h"
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


    void on_btnAddDay_clicked();

    void on_btnDeleteDay_clicked();

private:
    void setupConnections();
    Ui::accountingassessments *ui;
    std::unique_ptr<ImportSaveData> obj;
    std::unique_ptr<SerializerData> ser;
    std::unique_ptr<IODataBaseHandler> dbHandler;
    std::unique_ptr<TableManager> tabManager;
    MainWindow* backWindow;
    FileManager* fileManager;

    QAction* SaveJSON  ;
    QAction* UploadJSON;
    QAction* SaveDB    ;
    QAction* UploadDB  ;
    QAction* Print   ;
    QAction* Help      ;
    QAction* Quit      ;

   inline static int days = 0;

   static inline int column_day = 6;



};

#endif // ACCOUNTINGASSESSMENTS_H
