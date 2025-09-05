#include "studentdataservice.h"
#include "ui_studentdataservice.h"
#include"DynamicFormDialog.h"

StudentDataService::StudentDataService(MainWindow* main, QWidget *parent)
    : QWidget(parent)
    , mainWindow(main)
    , ui(new Ui::StudentDataService)
{

    ui->setupUi(this);

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
    DynamicDialog dlg(DynamicDialog::Mode::AddStudent, this);
    dlg.exec();
}

void StudentDataService::onPrintFile()
{
    DynamicDialog dlg(DynamicDialog::Mode::PreviewFile, this);
    dlg.exec();
}
void StudentDataService::onSortStudent()
{
    DynamicDialog dlg(DynamicDialog::Mode::SortStudent, this);
    dlg.exec();
}
void StudentDataService::onDeleteStudent()
{
    DynamicDialog dlg(DynamicDialog::Mode::DeleteStudent, this);
    dlg.exec();
}
void StudentDataService::onFindStudent()
{
    DynamicDialog dlg(DynamicDialog::Mode::FindStudent, this);
    dlg.exec();
}

void StudentDataService::backMainMenu()
{

    if (mainWindow) {
        mainWindow->show();
    }
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

}
