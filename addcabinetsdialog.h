#ifndef ADDCABINETSDIALOG_H
#define ADDCABINETSDIALOG_H

#include <QDialog>
#include"dataschedule.h"
#include"FileManagerCore/managerfs.h"
#include"schedulejsonparser.h"
namespace Ui {
class AddCabinetsDialog;
}

class AddCabinetsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCabinetsDialog(QWidget *parent = nullptr);
    ~AddCabinetsDialog();
private slots:
    bool SendCabinetsDataToJson();

private:
    Ui::AddCabinetsDialog *ui;
    std::unique_ptr<DataSchedule> schedule;

    std::unique_ptr<ScheduleJsonParser> parseJson;
};

#endif // ADDCABINETSDIALOG_H
