#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../include/Student.h"
#include <QMessageBox>
#include <QDebug>

Stud manag("Log.txt");


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditPassword->setStyleSheet("color: black;");


    ui->lineEditPassword->setEchoMode(QLineEdit::Password);

    connect(ui->pushButtonAuth, &QPushButton::clicked, this, &MainWindow::PushButtonAuth_clicked);
    connect(ui->pushButtonReg, &QPushButton::clicked, this, &MainWindow::PushButtonReg_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PushButtonAuth_clicked() {
    QString login = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();

    std::string loginStr = login.toStdString();
    std::string passwordStr = password.toStdString();


    bool auth = manag.loginStudent(loginStr, passwordStr);

    if (auth) {
        QMessageBox::information(this, "Вход", "Авторизация успешна!");
    } else {
        QMessageBox::warning(this, "Вход", "Неверный логин или пароль.");
    }
}

void MainWindow::PushButtonReg_clicked() {
    QString login = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();

    std::string loginStr = login.toStdString();
    std::string passwordStr = password.toStdString();


    bool reg = manag.registerStudent(loginStr, passwordStr);

    if (reg) {
        QMessageBox::information(this, "Регистрация", "Успешно!");
    } else {
        QMessageBox::warning(this, "Регистрация", "Не удалось зарегистрироваться.");
    }
}


