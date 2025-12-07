#ifndef FILECHOOICER_H
#define FILECHOOICER_H
#include<QString>
#include <QFileDialog>
#include <QMessageBox>
#include<QWidget>


class FileManager : public QWidget
{
    Q_OBJECT
public:
    explicit FileManager(QWidget *parent = nullptr);
    QString chooseFile();
    QString saveFile();
    QString chooseFileJson();
    QString saveFilePDF();
    QString chooseFileAbsolute();
    QString saveAbsoluteFile();
    //SQL
    QString saveDB();
    QString ChoiceDB();

private:
};



#endif // FILECHOOICER_H
