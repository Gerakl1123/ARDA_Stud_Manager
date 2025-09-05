#ifndef FILECHOOICER_H
#define FILECHOOICER_H
#include<QString>
#include <QFileDialog>
#include <QMessageBox>

class QWidget;

class FileManager
{
public:
    explicit FileManager(QWidget *parent = nullptr);
    QString chooseFile();
    QString saveFile();
    QString chooseFileJson();
    QString saveFilePDF();

private:
    QWidget *parentWidget;
};



#endif // FILECHOOICER_H
