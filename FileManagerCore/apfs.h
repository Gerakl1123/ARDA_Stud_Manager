#ifndef APFS_H
#define APFS_H

#include <QWidget>
#include<QFileSystemModel>
#include<memory>
#include<QDir>
#include<QThread>
enum class ModeView
{
    File,
    Dir
};

struct FileStats {
    int dirs;
    int files;
};

class filemanagerdialog;
class APFSworker;
namespace Ui {
class APFS;
}

class APFS : public QWidget
{
    Q_OBJECT

public:
    explicit APFS(filemanagerdialog* fmd,QWidget *parent = nullptr);
    ~APFS();
signals:
    void startOperation(ModeView mode,const QString &path);
private slots:
    void onCountFilesClicked();
    void on_tableView_doubleClicked(const QModelIndex &index);
    void Back();
private:
    QModelIndex index;
    Ui::APFS *ui;
    QThread* thread;
    QFileSystemModel* model;
    filemanagerdialog* fmd_;
    APFSworker* worker;
};

class APFSworker : public QObject
{
    Q_OBJECT
public:
    //APFSworker(QObject* parent = nullptr);
    ~APFSworker() override = default;
signals:
    void requestInfoTextEdit(const QString& msg);
    void progressValuer(int value);
    void finished();
public:
    bool viewInfoObject(ModeView mode, const QString& path);
    qint64 getSizeTravelDirectiry(const QString& path);
    QString getFullPath(const QString& path);
    QString getInfoExtra(const QString& path);
private:
    FileStats recursiveDirTraversal(const QString &path);
    qint64 getRecursiveMKpath(const QString& path);
};

#endif // APFS_H
