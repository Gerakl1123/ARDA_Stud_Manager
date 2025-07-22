#include "mainwindow.h"
#include<ui_mainwindow.h>
#include "./ui_mainwindow.h"
#include "../include/Student.h"
#include <QMessageBox>
#include <QDebug>
#include<QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //styleMainW();

    connect(ui->ButtonStudent,&QPushButton::clicked,this,&MainWindow::openManagerStud);
    connect(ui->ButtonContest,&QPushButton::clicked,this,&MainWindow::openContestWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::styleMainW()
{

    this->setStyleSheet(R"(
    QWidget {
    background-image: url(:/ico/s.png);
        background-repeat: no-repeat;
        background-position: center;
    }
        QPushButton {
            background-color: #4fc3f7;
            color: white;
            border: none;
            border-radius: 10px;
            padding: 10px 20px;
            font-size: 16px;
            font-weight: bold;
        }

        QPushButton:pressed {
            background-color: #1e88e5;
        }

    )");

}


void MainWindow::openManagerStud()
{

    qDebug() << "openManagerStud() вызван";
    windowStudent = std::make_unique<WindowsManagerStudent>(nullptr);

    if (windowStudent) {
        qDebug() << "Окно создано";
        this->close();
        windowStudent->show();

    } else {
        qDebug() << "Не удалось создать окно";
    }
}

void MainWindow::openContestWindow()
{
    qDebug() << "openconest() вызван ";
    windowContest = std::make_unique<contestwindow>(nullptr);

    if (windowContest) {
        qDebug() << "Окно создано";
        this->close();
        windowContest->show();

    }
    else {
        qDebug() << "Не удалось создать окно";
    }


}


