#ifndef RECORDBOOK_H
#define RECORDBOOK_H

#include <QWidget>
#include"IODataHandler.h"
#include"LogicOperation.h"
#include<QTableWidgetItem>
#include"Serializer.h"

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
    std::unique_ptr<FileManager> fileManager;
    std::unique_ptr<SerializerData> serilizer;

    void setupConnections();
    const int checkboxColumn = 6;
    const int resultColumn = 7;
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
