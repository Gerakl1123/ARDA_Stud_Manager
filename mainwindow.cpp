#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../include/Student.h"
#include <QMessageBox>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


