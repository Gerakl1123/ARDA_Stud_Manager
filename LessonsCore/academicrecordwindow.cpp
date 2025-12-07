#include "academicrecordwindow.h"
#include "ui_academicrecordwindow.h"
#include"../mainwindow.h"

academicrecordwindow::academicrecordwindow(MainWindow* main, QWidget *parent)
    : QWidget(parent)
    , mainwindow(main)
    , ui(new Ui::academicrecordwindow)

{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    this->setWindowIcon(QIcon("C:/Users/Gera/Desktop/JSONS/MenuLesson.png"));
    setWindowTitle("Учеты Студентов");
    setMaximumWidth(640);
    setMaximumHeight(480);
    setMinimumHeight(480);
    setMinimumWidth(640);

    connect(ui->btnCourseworkStart,&QPushButton::clicked,this,&academicrecordwindow::openCourseWork);
    connect(ui->btnBack,&QPushButton::clicked,this,&academicrecordwindow::BackMenu);
    connect(ui->btnLessonsStart,&QPushButton::clicked,this,&academicrecordwindow::openLessons);
    connect(ui->btnTestStart,&QPushButton::clicked,this,&academicrecordwindow::openRecorderBooks);
    connect(ui->btnProjectStart,&QPushButton::clicked,this,&academicrecordwindow::openProject);
    connect(ui->btnDiplomStart,&QPushButton::clicked,this,&academicrecordwindow::openDiploma);


}

academicrecordwindow::~academicrecordwindow()
{
    delete ui;

}

void academicrecordwindow::openLessons()
{
    accountingassessments* lesson = new accountingassessments(mainwindow);
    lesson->setAttribute(Qt::WA_DeleteOnClose);
    lesson->show();
    this->close();
}

void academicrecordwindow::BackMenu()
{
    mainwindow->show();
    this->close();
}


void academicrecordwindow::openRecorderBooks()
{
    RecordBook* recorderBook = new RecordBook(mainwindow);
    recorderBook->setAttribute(Qt::WA_DeleteOnClose);
    recorderBook->show();
    this->close();
}

void academicrecordwindow::openProject()
{
    project* projects = new project(mainwindow);
    projects->setAttribute(Qt::WA_DeleteOnClose);
    projects->show();
    this->close();
}

void academicrecordwindow::openCourseWork()
{
    Coursework* course = new Coursework(mainwindow);
    course->setAttribute(Qt::WA_DeleteOnClose);
    course->show();
    this->close();
}

void academicrecordwindow::openDiploma()
{
    Diploma* diploma = new Diploma(mainwindow);
    diploma->setAttribute(Qt::WA_DeleteOnClose);
    diploma->show();
    this->close();
}
