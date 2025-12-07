#ifndef BACKUP_H
#define BACKUP_H

#include <QWidget>
#include<QDir>
#include<QFileSystemModel>
#include<QThread>
#include<QTextEdit>
#include"../confrimdialog.h"
#include<QItemSelection>

class filemanagerdialog;
class BackupWorker;
namespace Ui {
class BackUp;
}

class BackUp : public QWidget
{
    Q_OBJECT

public:
    explicit BackUp(filemanagerdialog* fmd,QWidget *parent = nullptr);
    ~BackUp();
private slots:

    void on_sourceB_doubleClicked(const QModelIndex &index);
    void Back();
    // To Do
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
signals:
    void startOperration(QString sPath,QString bPath);
    void startOperation(QFileInfoList list,QString b);
private:
    QThread* thread;
    Ui::BackUp *ui;
    QFileSystemModel* model;
    filemanagerdialog* fmd_;
    BackupWorker* worker;
    QFileInfoList files_;
    ConfrimDialog* confrimDialog_;
};

class BackupWorker : public QObject {
    Q_OBJECT

public slots:

void runBackUp(QString sPath,QString bPath);

    bool runBackUpNew(QFileInfoList files, QString dPath);
signals:
    void logMessage(const QString &msg);
    void finishedCopy();
    void progressChanged(int value);
    void unlockBTN();
private:

    void recursiveList(QDir& sDir,QFileInfoList& filesList);
    void compareDirs(QDir& sdir,QDir& ddir,QFileInfoList& fileList);
    bool StorageBackup(QDir& s, QDir &b);
    qint64 getTotalSizeMBDirsCopy(QDir& s);
//To DO
private:
    bool recursiveCopy(QString& sPath,QString &dPath);
};

#endif // BACKUP_H
