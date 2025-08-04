/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#include "mainwindow.h"
#include<ui_mainwindow.h>
#include "./ui_mainwindow.h"
#include "../include/Student.h"
#include <QMessageBox>
#include <QDebug>
#include<QIcon>
#include<QStyleFactory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //styleMainW()
    connect(ui->pushButtonAppStyle, &QPushButton::clicked, this,&MainWindow::ToggleStyleApp);
    connect(ui->ButtonStudent,&QPushButton::clicked,this,&MainWindow::openManagerStud);
    connect(ui->ButtonContest,&QPushButton::clicked,this,&MainWindow::openContestWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete windowStudent;
    delete windowContest;
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
    windowStudent = new StudentDataService();

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

    windowContest = new contestwindow(this);
    if (windowContest) {
        qDebug() << "Окно создано";
        this->close();
        windowContest->show();

    }
    else {
        qDebug() << "Не удалось создать окно";
    }


}

void MainWindow::ToggleStyleApp()
{
    if (!StyleChoice) {
        qApp->setStyle(QStyleFactory::create("Fusion"));

        QPalette darkPalette;
        darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(42, 42, 42));
        darkPalette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Highlight, QColor(142, 45, 197).lighter());
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);

        qApp->setPalette(darkPalette);

        StyleChoice = true;

    } else {

        qApp->setStyle(QStyleFactory::create("Fusion"));

        QPalette lightPalette;
        lightPalette.setColor(QPalette::Window, QColor(255, 255, 255));
        lightPalette.setColor(QPalette::WindowText, Qt::black);
        lightPalette.setColor(QPalette::Base, QColor(245, 245, 245));
        lightPalette.setColor(QPalette::AlternateBase, QColor(255, 255, 255));
        lightPalette.setColor(QPalette::ToolTipBase, Qt::black);
        lightPalette.setColor(QPalette::ToolTipText, Qt::white);
        lightPalette.setColor(QPalette::Text, Qt::black);
        lightPalette.setColor(QPalette::Button, QColor(240, 240, 240));
        lightPalette.setColor(QPalette::ButtonText, Qt::black);
        lightPalette.setColor(QPalette::BrightText, Qt::red);
        lightPalette.setColor(QPalette::Highlight, QColor(76, 163, 224));
        lightPalette.setColor(QPalette::HighlightedText, Qt::white);

        qApp->setPalette(lightPalette);

        StyleChoice = false;
    }

}


