#ifndef CREATEFILEDIALOG_H
#define CREATEFILEDIALOG_H

#include <QDialog>

namespace Ui {
class CreateFileDialog;
}

class CreateFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateFileDialog(QWidget *parent = nullptr);
    ~CreateFileDialog();
    QString getFileName();

private:
    Ui::CreateFileDialog *ui;
};

#endif // CREATEFILEDIALOG_H
