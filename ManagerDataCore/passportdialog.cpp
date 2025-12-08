#include "passportdialog.h"
#include "ui_passportdialog.h"
#include<QDateEdit>
#include<QComboBox>
#include<QPushButton>
#include"../JsonKeys.h"
#include"../Serializer.h"
PassportDialog::PassportDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PassportDialog)
{
    ui->setupUi(this);
    ser = new SerializerData(this);

    ui->lineEditName->setPlaceholderText("Имя");
    ui->lineEditMiddleName->setPlaceholderText("Фамилия");
    ui->lineEditLastName->setPlaceholderText("Отчество(если есть)");
    ui->lineEditAddress->setPlaceholderText("Адресс проживания");
    ui->lineEditSeria->setPlaceholderText("Серия Пасспорта");
    ui->lineEditNumberPassport->setPlaceholderText("Номер Пасспорта");
    ui->lineEditBirthPlace->setPlaceholderText("Место рождения");
    ui->lineEditCodePodr->setPlaceholderText("Код подразделения");
    ui->lineEditKemVidan->setPlaceholderText("Кем выдан");
    ui->comboBoxGender->setPlaceholderText("Пол");
    ui->comboBoxGrazdanstvo->setPlaceholderText("Гражданство");

    ui->comboBoxGender->addItems(Passport::gender);
    ui->comboBoxGrazdanstvo->addItems(Passport::citizenship);

    parser = std::make_unique<ParserJson>();

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, [=]() {
        parser->SaveJsonPassport(this);
    });

    ser->DataSerelizationPassport(this);

}

PassportDialog::~PassportDialog()
{

    ser->DataSerelizationPassport(this);
    delete ui;
}
