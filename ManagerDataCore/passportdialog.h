#ifndef PASSPORTDIALOG_H
#define PASSPORTDIALOG_H

#include <QDialog>
#include"../parserjson.h"
#include"../Serializer.h"

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
    SerializerData* ser;
};

#endif // PASSPORTDIALOG_H
