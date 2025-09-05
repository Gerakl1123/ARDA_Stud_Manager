#ifndef PROJECT_H
#define PROJECT_H

#include <QWidget>
#include"IODataHandler.h"
#include"Serializer.h"
#include"FileChooicer.h"

class MainWindow;

namespace Ui {
class project;
}

class project : public QWidget
{
    Q_OBJECT

public:
    explicit project(MainWindow* main,QWidget *parent = nullptr);
    ~project();

private:
    Ui::project *ui;
    MainWindow* mainWindow;
    std::unique_ptr<ImportSaveData> isd;
    std::unique_ptr<SerializerData> ser;
    std::unique_ptr<FileManager> fileManager;

    void setupConnections();
private slots:
    void DeleteRow();
    void PrintData();
    void findName();
    void ClearTable();

};

#endif // PROJECT_H
