#include "priviewstudentdialog.h"
#include "ui_priviewstudentdialog.h"
#include"../LogicOperation.h"
#include"../Serializer.h"

PriviewStudentDialog::PriviewStudentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PriviewStudentDialog)
{
    ui->setupUi(this);

    fileManager = new FileManager(this);
    SerializerData* ser = new SerializerData(this);
    connect(ui->btnOk,&QPushButton::clicked,this,&PriviewStudentDialog::priviewStudent);
    connect(ui->btnClose,&QPushButton::clicked,this,[=](){
        this->close();
    });

    BuilderForm::setupBrowseButton(ui->btnBrowse,ui->lineEditFile_ManagerStudent_,fileManager);

    ser->DataSerelization(this,ModeSerelization::ManagerStudent);
}

PriviewStudentDialog::~PriviewStudentDialog()
{
    delete ui;

}

void PriviewStudentDialog::priviewStudent()
{
    LogicOperation l;

    QString file = ui->lineEditFile_ManagerStudent_->text();
    l.handlePriviewFile(file,ui->textEdit,this);
}
