#ifndef RECORDBOOK_H
#define RECORDBOOK_H

#include <QWidget>
#include"../IOCore/IODataHandler.h"
#include"../LogicOperation.h"
#include<QTableWidgetItem>
#include"../Serializer.h"
#include"../IOCore/iodatabasehandler.h"
class MainWindow;

namespace Ui {
class RecordBook;
}

class RecordBook : public QWidget
{
    Q_OBJECT

public:
    explicit RecordBook(MainWindow* main, QWidget *parent = nullptr);
    ~RecordBook();

private:
    Ui::RecordBook *ui;
    MainWindow* backWindow;
    ImportSaveData* obj;
    LogicOperation* ihs;
    std::unique_ptr<IODataBaseHandler> dbHandler;
    FileManager* fileManager;
    std::unique_ptr<SerializerData> serilizer;

    void setupConnections();
    const int checkboxColumn = 7;
    const int resultColumn = 8;
private slots:
    void Back();

    void addRow();

    void DeleteRow();

    void ClearTable();

    void PrintData();

    void FindName();

    void AutoTest(QTableWidgetItem* item);
};

#endif // RECORDBOOK_H
