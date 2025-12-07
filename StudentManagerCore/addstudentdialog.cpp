#include "addstudentdialog.h"
#include "ui_addstudentdialog.h"
#include"../LogicOperation.h"
#include"../builderform.h"

AddStudentDialog::AddStudentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddStudentDialog)
{
    ui->setupUi(this);

    FileManager* fileManager = new FileManager(this);

    SerializerData* ser = new SerializerData(this);
    connect(ui->btnOk,&QPushButton::clicked,this,&AddStudentDialog::addStudent);

    connect(ui->btnClose,&QPushButton::clicked,this,[=](){
        this->close();
    });

    BuilderForm::setupBrowseButton(ui->btnBrowse,ui->lineEditFile,fileManager);
    ser->DataSerelization(this,ModeSerelization::ManagerStudent);

}

AddStudentDialog::~AddStudentDialog()
{
    delete ui;
}

bool AddStudentDialog::addStudent()
{
    LogicOperation l;
    QString file = ui->lineEditFile->text().toUtf8();
    QString data = ui->lineEditData->text().toUtf8();

    bool result = l.handleAddStudent(file,data,ui->lineEditData,this);

    return result;

}



