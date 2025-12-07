#include "findstudentdialog.h"
#include "ui_findstudentdialog.h"
#include"../LogicOperation.h"

FindStudentDialog::FindStudentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FindStudentDialog)
{
    ui->setupUi(this);

    fileManager = new FileManager(this);

    SerializerData* ser = new SerializerData(this);

    connect(ui->btnOk,&QPushButton::clicked,this,&FindStudentDialog::FindStudent);
    connect(ui->btnClose,&QPushButton::clicked,this,[=](){
        this->close();
    });

    BuilderForm::setupBrowseButton(ui->btnBrowse,ui->lineEditFile,fileManager);

    ser->DataSerelization(this,ModeSerelization::ManagerStudent);

}

FindStudentDialog::~FindStudentDialog()
{
    delete ui;
}

void FindStudentDialog::FindStudent()
{
    LogicOperation l;

    QString file = ui->lineEditFile->text();
    QString name = ui->lineEditName->text();
    QString score = ui->lineEditBall->text();

    l.handleFindStudent(file,name,score,this);
}
