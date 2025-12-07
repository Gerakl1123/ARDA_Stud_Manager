#ifndef DELETESTUDENTDIALOG_H
#define DELETESTUDENTDIALOG_H

#include <QDialog>
#include"../FileChooicer.h"
#include"../builderform.h"

namespace Ui {
class DeleteStudentDialog;
}

class DeleteStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteStudentDialog(QWidget *parent = nullptr);
    ~DeleteStudentDialog();

private:
    Ui::DeleteStudentDialog *ui;
    BuilderForm* temp;
    FileManager* fileManager;
private slots:
    void DeleteStudent();
};

#endif // DELETESTUDENTDIALOG_H
