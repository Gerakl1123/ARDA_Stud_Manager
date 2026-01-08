#ifndef EXTRADATADIALOG_H
#define EXTRADATADIALOG_H

#include <QDialog>
#include"../passportdatajsonparser.h"
#include<QPushButton>
#include"../Serializer.h"
namespace Ui {
class ExtraDataDialog;
}

class ExtraDataDialog final : public QDialog
{
    Q_OBJECT

public:
    explicit ExtraDataDialog(QWidget *parent = nullptr);
    ~ExtraDataDialog();


private:
    Ui::ExtraDataDialog *ui;
    std::unique_ptr<PassportDataJSONParser> parser;
    SerializerData* ser;
};

#endif // EXTRADATADIALOG_H
