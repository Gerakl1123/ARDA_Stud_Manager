#ifndef MANAGERFS_H
#define MANAGERFS_H

#include <QWidget>
#include<QFileSystemModel>
#include<QDir>
#include<QFile>
#include<QComboBox>
#include"../confrimdialog.h"
#include"../Logger.h"
#include<QThread>
#include<QItemSelection>
#include"../Logger.h"
#include "../builderform.h"
#include<QSortFilterProxyModel>
#include"createfiledialog.h"

enum class OperationState {
    Success,
    Exists,
    Error
};

static inline std::shared_ptr<Log> logger = Log::create("FileManager.log");

class filemanagerdialog;
class ManagerWorker;
namespace Ui {
class ManagerFS;
}

class ManagerFS : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerFS(filemanagerdialog* dlg, QWidget *parent = nullptr);
    ~ManagerFS();

private slots:

    void onDirectoryOperationResult(OperationState state,  const QString &msg);
    void onFilesOperationResult(OperationState state,  const QString &msg);
    void Back();
    void onCreateDirClicked();
    void onCreateFileClicked();
    void on_tableView_doubleClicked(const QModelIndex &index);
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
signals:
    void requestCreateDir(const QString& path,const QString& name);
    void requestCreateFile(const QString& path,const QString& name);
    void requestSeletcerFilesObjects(const QFileInfoList& listPaths);
    void requestRenameDir(const QString& oldPath,const QString& newName);
    void requestRenameFile(const QString& name);
    void getFiles(QFileInfoList list);
private:
    QThread* threadWorker;
    Ui::ManagerFS *ui;
    QFileSystemModel* model;
    filemanagerdialog* dlg_;
    ManagerWorker* worker;
    QFileInfoList files_;
    QCheckBox* defaultExtesions;
    BuilderForm* buildForm_;
    CreateFileDialog* createFile;
    QSortFilterProxyModel* SortModel;
    ConfrimDialog* confrimDialog_;
};

class ManagerWorker : public QObject
{
    Q_OBJECT

public:
    ManagerWorker(QObject* parent = nullptr);
    bool CreateDir(const QString& path,const QString& fileName);
    bool CreateFile(const QString& path, const QString& fileName);

    void setFiles(QFileInfoList list);
public slots:
    bool removeDir(const QString &path);
    bool removeFile(const QString &path);
    bool renameFile(const QString& name);
    bool renameDir(const QString& oldName,const QString& name);
    void RemoveSelecteFilesObjects(const QFileInfoList &files);
signals:
    void succesMessageCreateDir(OperationState state,const QString& msg);
    void succesMessageCreateFile(OperationState state,const QString& msg);

    void getMessageLogDeleted(const QString& msg);
        void finished(bool state);
private:
    QString nameFile;
    QFileInfoList files;
};

#endif // MANAGERFS_H
