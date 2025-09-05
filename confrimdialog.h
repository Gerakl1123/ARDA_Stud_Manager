#ifndef CONFRIMDIALOG_H
#define CONFRIMDIALOG_H

#include <QDialog>

namespace Ui {
class ConfrimDialog;
}

class ConfrimDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfrimDialog(QWidget *parent = nullptr);
    ~ConfrimDialog();

private:
    Ui::ConfrimDialog *ui;
};

#endif // CONFRIMDIALOG_H
