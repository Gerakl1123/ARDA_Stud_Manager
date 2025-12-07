#ifndef FINDSTUDENTDIALOG_H
#define FINDSTUDENTDIALOG_H

#include <QDialog>
#include"../builderform.h"
#include"../FileChooicer.h"

namespace Ui {
class FindStudentDialog;
}

class FindStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindStudentDialog(QWidget *parent = nullptr);
    ~FindStudentDialog();

private:
    Ui::FindStudentDialog *ui;
    BuilderForm* temp;
    FileManager* fileManager;
private slots:
    void FindStudent();
};

#endif // FINDSTUDENTDIALOG_H
