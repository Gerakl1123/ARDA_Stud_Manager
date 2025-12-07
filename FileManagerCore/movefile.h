#ifndef MOVEFILE_H
#define MOVEFILE_H

#include <QWidget>
#include<QItemSelection>
#include<QFileInfoList>
#include<QFileSystemModel>
#include"../builderform.h"
#include"../Logger.h"
#include<QThread>
class filemanagerdialog;
class MoveFileWorker;
namespace Ui {
class MoveFile;
}

class MoveFile : public QWidget
{
    Q_OBJECT


    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
public:
    explicit MoveFile(filemanagerdialog* FMD,QWidget *parent = nullptr);
    ~MoveFile();

    inline static std::shared_ptr<Log> logger = Log::create("MoveFiles.log");
private slots:
    void on_listView_doubleClicked(const QModelIndex &index);
    void BackMenu();
signals:
    void startOperation(QFileInfoList files, QString s);
    void startOperationAll(QString s,QString b);

private:
    QFileInfoList files_;
    QString sourcePath;
    QFileSystemModel* model;
    MoveFileWorker* worker;
    BuilderForm* formBuilder;
    filemanagerdialog* dlg_;
    QThread* threadWorker;
    Ui::MoveFile *ui;
};

class MoveFileWorker : public QObject
{
    Q_OBJECT

signals:
    void SuccesOperation(bool succes);
    void SuccesOperationAll(bool success);
public slots:

    bool runMoveFile(QFileInfoList listFiles, QString bDir);
    bool moveDirectoryRecursive(const QString &sourceDir, const QString &destDir);

    //ALL
    bool runMoveFileAll(QString bPath, QString sPath);

};

#endif // MOVEFILE_H
