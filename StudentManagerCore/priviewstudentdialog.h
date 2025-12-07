#ifndef PRIVIEWSTUDENTDIALOG_H
#define PRIVIEWSTUDENTDIALOG_H

#include <QDialog>
#include"../FileChooicer.h"
#include"../builderform.h"
#include"../Serializer.h"
#include"../settingsbinder.h"

namespace Ui {
class PriviewStudentDialog;
}

class PriviewStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PriviewStudentDialog(QWidget *parent = nullptr);
    ~PriviewStudentDialog();

private:
    Ui::PriviewStudentDialog *ui;
    FileManager* fileManager;
  SerializerData* ser;
public slots:
    void priviewStudent();
};

#endif // PRIVIEWSTUDENTDIALOG_H
