#include "mainwindow.h"
#include<ui_mainwindow.h>
#include "./ui_mainwindow.h"
#include "../include/Student.h"
#include <QMessageBox>
#include <QDebug>
#include<QIcon>
#include "windowsmanagerstudent.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //styleMainW();

    connect(ui->ButtonStudent,&QPushButton::clicked,this,&MainWindow::openManagerStud);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::styleMainW()

{

    this->setStyleSheet(R"(
        QWidget {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                        stop:0 #1e3c72, stop:1 #2a5298);
        }

        QPushButton {
            background-color: #4fc3f7;
            color: white;
            border: none;
            border-radius: 10px;
            padding: 10px 20px;
            font-size: 16px;
            font-weight: bold;
            transition: all 0.2s ease;
        }
    )");

}


void MainWindow::openManagerStud()
{

    qDebug() << "openManagerStud() вызван";
    window = std::make_unique<WindowsManagerStudent>(nullptr);

    if (window) {
        qDebug() << "Окно создано";
        this->close();
        window->show();

    } else {
        qDebug() << "Не удалось создать окно";
    }
}
