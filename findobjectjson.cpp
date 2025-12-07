#include "findobjectjson.h"
#include "ui_findobjectjson.h"

FindObjectJson::FindObjectJson(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FindObjectJson)
    ,fileManager(new FileManager(this))
{
    ui->setupUi(this);
    ui->lineEditID->setPlaceholderText("Введите ID ученика которого ищите");

    ui->lineEditFileName->setPlaceholderText("Файл с данными");

    connect(ui->lineEditID,&QLineEdit::editingFinished,this,[this](){
        emit getID(ui->lineEditID->text());
    });

    connect(ui->lineEditFileName,&QLineEdit::editingFinished,this,[this](){
        emit getNameFile(ui->lineEditFileName->text());
    });

    connect(ui->btnBrowse,&QPushButton::clicked,this,[this](){
        ui->lineEditFileName->setText(fileManager->chooseFileJson());
        emit getNameFile(ui->lineEditFileName->text());
    });

    connect(ui->lineEditExtraData,&QLineEdit::editingFinished,this,[this](){
        emit getNameFileExtra(ui->lineEditExtraData->text());
    });

    connect(ui->btnBrowseExtra,&QPushButton::clicked,this,[this](){
        ui->lineEditExtraData->setText(fileManager->chooseFileJson());
        emit getNameFileExtra(ui->lineEditExtraData->text());
    });

    connect(ui->buttonBox->button(QDialogButtonBox::Ok),&QPushButton::clicked,this,[this](){
        emit FillList();
    });

}

FindObjectJson::~FindObjectJson()
{
    delete ui;
}
