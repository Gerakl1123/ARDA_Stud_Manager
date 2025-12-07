#ifndef ADDEDOBJECTFILES_H
#define ADDEDOBJECTFILES_H

#include <QWidget>
#include<QFileSystemModel>
#include<QItemSelection>



class filemanagerdialog;

namespace Ui {
class AddedObjectFiles;
}

class AddedObjectFiles : public QWidget
{
    Q_OBJECT

public:
    explicit AddedObjectFiles(filemanagerdialog* fmd,QWidget *parent = nullptr);
    ~AddedObjectFiles();

public slots:
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    bool  zipData();
private slots:
    void on_listView_doubleClicked(const QModelIndex &index);

private:
    QFileInfoList files_;
    Ui::AddedObjectFiles *ui;
    QFileSystemModel* model;
    filemanagerdialog* fmd_;
    void backMenu();
};

#endif // ADDEDOBJECTFILES_H
