#include "academicrecordwindow.h"
#include "ui_academicrecordwindow.h"
#include"mainwindow.h"

academicrecordwindow::academicrecordwindow(MainWindow* main, QWidget *parent)
    : QWidget(parent)
    , mainwindow(main)
    , ui(new Ui::academicrecordwindow)
    ,Projects(new project(main,parent))
    , RecorderBook(new RecordBook(main,parent))
    , lesson(new accountingassessments(main,parent))
    , course(new Coursework(main,parent))
    , diplom(new Diploma(main,parent))
{
    ui->setupUi(this);

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
    lesson->show();
    this-close();
}

void academicrecordwindow::BackMenu()
{
    mainwindow->show();
    this->close();
}


void academicrecordwindow::openRecorderBooks()
{
    RecorderBook->show();
    this->close();
}

void academicrecordwindow::openProject()
{
    Projects->show();
    this->close();
}

void academicrecordwindow::openCourseWork()
{
    course->show();
    this->close();
}

void academicrecordwindow::openDiploma()
{
    this->close();
    diplom->show();
}
