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

    ser = new SerializerData(this);

    connect(ui->checkBoxPreviousPlace,&QCheckBox::checkStateChanged,this,[=](Qt::CheckState state){
        if(static_cast<int>(state) == 2)
        {
            ui->lineEditSerialDiploma->setReadOnly(false);
            ui->lineEditGetDiploma->setReadOnly(false);
            ui->spinBoxYearDiploma->setReadOnly(false);
            ui->checkBoxDiploma->setCheckable(true);
        }else
        {

            ui->lineEditSerialDiploma->setReadOnly(true);
            ui->lineEditGetDiploma->setReadOnly(true);
            ui->spinBoxYearDiploma->setReadOnly(true);
            ui->checkBoxDiploma->setCheckable(false);
        }
    });

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, [=]() {
        parser->SaveJsonExtraData(this);
    });

    ser->DataSerelizationExtra(this);


}

ExtraDataDialog::~ExtraDataDialog()
{
    ser->DataSerelizationExtra(this);

    delete ui;
}


