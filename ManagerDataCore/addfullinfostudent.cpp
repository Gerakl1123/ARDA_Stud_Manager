#include "addfullinfostudent.h"
#include "ui_addfullinfostudent.h"
#include"passportdialog.h"
#include"../StudentManagerCore/studentdataservice.h"
#include"extradatadialog.h"

AddFullInfoStudent::AddFullInfoStudent(StudentDataService* pStudentData, QWidget *parent)
    : QWidget(parent)
    , StudentDataS(pStudentData)
    , ui(new Ui::AddFullInfoStudent)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->btnPassport,&QPushButton::clicked,this,&AddFullInfoStudent::openPassportData);
    connect(ui->btnLeave,&QPushButton::clicked,this,&AddFullInfoStudent::BackMenu);
    connect(ui->btnExtraData,&QPushButton::clicked,this,&AddFullInfoStudent::openExtraData);
}

AddFullInfoStudent::~AddFullInfoStudent()
{
    delete ui;
}

void AddFullInfoStudent::openPassportData()
{

    PassportDialog dlg(this);
    dlg.exec();
}

void AddFullInfoStudent::openExtraData()
{
    ExtraDataDialog dlg(this);
    dlg.exec();
}

void AddFullInfoStudent::BackMenu()
{
    this->close();
    StudentDataS->show();
}
