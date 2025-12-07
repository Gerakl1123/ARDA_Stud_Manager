#ifndef SORTSTUDENTDIALOG_H
#define SORTSTUDENTDIALOG_H

#include <QDialog>
#include"../FileChooicer.h"
#include"../builderform.h"

namespace Ui {
class SortStudentDialog;
}

class SortStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SortStudentDialog(QWidget *parent = nullptr);
    ~SortStudentDialog();

private:
    Ui::SortStudentDialog *ui;
    BuilderForm* temp;
    FileManager* fileManager;
private slots:
    bool SortStudent();

};

#endif // SORTSTUDENTDIALOG_H
