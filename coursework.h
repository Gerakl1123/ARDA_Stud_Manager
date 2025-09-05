#ifndef COURSEWORK_H
#define COURSEWORK_H

#include <QWidget>
#include<QComboBox>
#include<QDateEdit>
#include"IODataHandler.h"
#include"FileChooicer.h"
#include<QCheckBox>
#include"Serializer.h"

class MainWindow;

namespace Ui {
class Coursework;
}

class Coursework : public QWidget
{
    Q_OBJECT

public:
    explicit Coursework(MainWindow* mainWin,QWidget *parent = nullptr);
    ~Coursework();

private:
    Ui::Coursework *ui;
    MainWindow* main;
    std::unique_ptr<ImportSaveData> isd;
    std::unique_ptr<FileManager> fileManager;
    std::unique_ptr<SerializerData> ser;

    QComboBox* comBox;
    QDateEdit* DateEdit;
    QCheckBox *confirmCheckBox;
    QCheckBox* OnOffSerelization;
    void BackMenu();
public slots:
    void PrinterData();
    void addRow();
    void DeleteRow();
    void ClearTable();
    void findName(const QString& name);

};

#endif // COURSEWORK_H
