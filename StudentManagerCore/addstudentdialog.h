#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#include <QDialog>
#include"../FileChooicer.h"
#include<QLineEdit>
#include"../builderform.h"

namespace Ui {
class AddStudentDialog;
}

class AddStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddStudentDialog(QWidget *parent = nullptr);
    ~AddStudentDialog();

private:
    Ui::AddStudentDialog *ui;
    BuilderForm* temp;
    FileManager* manag;
private slots:
    bool addStudent();


};

#endif // ADDSTUDENTDIALOG_H
