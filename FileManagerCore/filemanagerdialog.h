#ifndef FILEMANAGERDIALOG_H
#define FILEMANAGERDIALOG_H

#include <QWidget>
#include"backup.h"
#include"managerfs.h"
#include"apfs.h"
#include"movefile.h"
#include"addedobjectfiles.h"
class MainWindow;

namespace Ui {
class filemanagerdialog;
}

class filemanagerdialog : public QWidget
{
    Q_OBJECT

public:
    explicit filemanagerdialog(MainWindow* main, QWidget *parent = nullptr);
    ~filemanagerdialog();

private slots:
    void openBackUp();
    void openManager();
    void openADMIN();
    void BackMenu();
    void MoveMenu();
    void ZIPMenu();
private:
    Ui::filemanagerdialog *ui;
    MainWindow* mainW;


};

#endif // FILEMANAGERDIALOG_H
