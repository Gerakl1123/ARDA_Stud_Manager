#include "deletestudentdialog.h"
#include "ui_deletestudentdialog.h"
#include"../LogicOperation.h"

DeleteStudentDialog::DeleteStudentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeleteStudentDialog)
{
    ui->setupUi(this);


    fileManager = new FileManager(this);

    SerializerData* ser = new SerializerData(this);
    connect(ui->btnOk,&QPushButton::clicked,this,&DeleteStudentDialog::DeleteStudent);
    connect(ui->btnClose,&QPushButton::clicked,this,[=](){
        this->close();
    });

    BuilderForm::setupBrowseButton(ui->btnBrowse,ui->lineEditFile,fileManager);
    ser->DataSerelization(this,ModeSerelization::ManagerStudent);



}

DeleteStudentDialog::~DeleteStudentDialog()
{
    delete ui;
}

void DeleteStudentDialog::DeleteStudent()
{
    LogicOperation l;

    QString file = ui->lineEditFile->text();
    QString name = ui->lineEditName->text();
    QString score = ui->lineEditBall->text();
    l.handleDeleteStudent(file,name,score,this);
}
