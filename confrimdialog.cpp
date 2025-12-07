#include "confrimdialog.h"
#include "ui_confrimdialog.h"

ConfrimDialog::ConfrimDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfrimDialog)
{
    ui->setupUi(this);
}

ConfrimDialog::~ConfrimDialog()
{
    delete ui;
}
