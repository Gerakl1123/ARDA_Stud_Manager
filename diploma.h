#ifndef DIPLOMA_H
#define DIPLOMA_H

#include <QWidget>
#include<QCheckBox>
#include"IODataHandler.h"
#include"FileChooicer.h"

class MainWindow;

namespace Ui {
class Diploma;
}

class Diploma : public QWidget
{
    Q_OBJECT

public:
    explicit Diploma(MainWindow* main,QWidget *parent = nullptr);
    ~Diploma();

private:
    Ui::Diploma *ui;
    MainWindow* mainWin;
    std::unique_ptr<ImportSaveData> isd;
    QCheckBox *confirmCheckBox;
    QCheckBox* OnOffSerelization;
    std::unique_ptr<FileManager> fileManager;
public slots:
    void addRow();
    void deleteRow();
    void ClearTable();
    void PrinterData();
    void backMain();

};

#endif // DIPLOMA_H
