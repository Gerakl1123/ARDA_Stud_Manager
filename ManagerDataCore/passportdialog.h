#ifndef PASSPORTDIALOG_H
#define PASSPORTDIALOG_H

#include <QDialog>
#include"../parserjson.h"
namespace Ui {
class PassportDialog;
}

class PassportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PassportDialog(QWidget *parent = nullptr);
    ~PassportDialog();

private:
    Ui::PassportDialog *ui;
    std::unique_ptr<ParserJson> parser;
};

#endif // PASSPORTDIALOG_H
