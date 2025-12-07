#include "extradatadialog.h"
#include "ui_extradatadialog.h"
#include<QDate>

ExtraDataDialog::ExtraDataDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExtraDataDialog)
{
    ui->setupUi(this);
    parser = std::make_unique<ParserJson>();
    ui->spinBoxYearGraduationAttestat->setValue(QDate::currentDate().year());
    ui->spinBoxYearDiploma->setValue(QDate::currentDate().year());

    connect(ui->checkBoxPreviousPlace,&QCheckBox::checkStateChanged,this,[=](Qt::CheckState state){
        if(static_cast<int>(state) == 2)
        {
            ui->lineEditSerialDiploma->setEnabled(true);
            ui->lineEditGetDiploma->setEnabled(true);
            ui->spinBoxYearDiploma->setReadOnly(false);
            ui->checkBoxDiploma->setEnabled(true);
        }else
        {

            ui->lineEditSerialDiploma->setEnabled(false);
            ui->lineEditGetDiploma->setEnabled(false);
            ui->spinBoxYearDiploma->setReadOnly(true);
            ui->checkBoxDiploma->setEnabled(false);
        }
    });

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, [=]() {
        parser->SaveJsonExtraData(this);
    });

}

ExtraDataDialog::~ExtraDataDialog()
{
    delete ui;
}


