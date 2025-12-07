#include "createfiledialog.h"
#include "ui_createfiledialog.h"
#include"../JsonKeys.h"
#include<QPushButton>
CreateFileDialog::CreateFileDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateFileDialog)
{
    ui->setupUi(this);
    ui->comboBoxExtions->addItems(extension::fileExtension);
    ui->comboBoxExtions->setCurrentText("");

}

CreateFileDialog::~CreateFileDialog()
{
    delete ui;
}

QString CreateFileDialog::getFileName()
{
    return ui->lineEdit->text() + ui->comboBoxExtions->currentText();
}

