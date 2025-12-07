#include "studentdataservice.h"
#include "ui_studentdataservice.h"
#include"addstudentdialog.h"
#include"../mainwindow.h"
#include"sortstudentdialog.h"
#include"deletestudentdialog.h"
#include"findstudentdialog.h"
#include"priviewstudentdialog.h"
#include"../ManagerDataCore/addfullinfostudent.h"

StudentDataService::StudentDataService(MainWindow* main, QWidget *parent)
    : QWidget(parent)
    , mainWindow(main)
    , ui(new Ui::StudentDataService)
{

    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowIcon(QIcon("C:/Users/Gera/Desktop/JSONS/Manager.png"));
    setWindowTitle("Менеджер Студентов");
    setupConnections();
}

StudentDataService::~StudentDataService()
{
    delete ui;
}

void StudentDataService::onAddStudentClicked()
{
    AddStudentDialog dlg(this);
    dlg.exec();
}

void StudentDataService::onPrintFile()
{
    PriviewStudentDialog dlg(this);
    dlg.exec();
}
void StudentDataService::onSortStudent()
{
    SortStudentDialog dlg(this);
    dlg.exec();
}
void StudentDataService::onDeleteStudent()
{
    DeleteStudentDialog dlg(this);
    dlg.exec();
}
void StudentDataService::onFindStudent()
{
    FindStudentDialog dlg(this);
    dlg.exec();
}

void StudentDataService::onAddInfoStud()
{
    AddFullInfoStudent* StudentInfo = new AddFullInfoStudent(this);
    StudentInfo->setAttribute(Qt::WA_DeleteOnClose);
    StudentInfo->show();
    this->hide();
}

void StudentDataService::backMainMenu()
{
    mainWindow->show();
    this->close();

}

void StudentDataService::setupConnections()
{
    connect(ui->pushButtonAddStudent,&QPushButton::clicked,this,&StudentDataService::onAddStudentClicked);
    connect(ui->pushButtonSeeFile,&QPushButton::clicked,this,&StudentDataService::onPrintFile);
    connect(ui->pushButtonBackMain,&QPushButton::clicked,this,&StudentDataService::backMainMenu);
    connect(ui->pushButtonSortStud,&QPushButton::clicked,this,&StudentDataService::onSortStudent);
    connect(ui->pushButtonDeleteStudent,&QPushButton::clicked,this,&StudentDataService::onDeleteStudent);
    connect(ui->pushButtonFindStudent,&QPushButton::clicked,this,&StudentDataService::onFindStudent);
    connect(ui->btnInfoStudent,&QPushButton::clicked,this,&StudentDataService::onAddInfoStud);

}
