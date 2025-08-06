#include "academicrecordwindow.h"
#include "ui_academicrecordwindow.h"
#include"mainwindow.h"

academicrecordwindow::academicrecordwindow(MainWindow* main, QWidget *parent)
    : QWidget(parent)
    , mainwindow(main)
    , ui(new Ui::academicrecordwindow)
    , lesson(new accountingassessments(main,parent))
{
    ui->setupUi(this);
    connect(ui->btnBack,&QPushButton::clicked,this,&academicrecordwindow::BackMenu);
    connect(ui->btnLessonsStart,&QPushButton::clicked,this,&academicrecordwindow::openLessons);
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
