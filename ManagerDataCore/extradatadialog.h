#ifndef EXTRADATADIALOG_H
#define EXTRADATADIALOG_H

#include <QDialog>
#include"../parserjson.h"
#include<QPushButton>
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
    std::unique_ptr<ParserJson> parser;
};

#endif // EXTRADATADIALOG_H
