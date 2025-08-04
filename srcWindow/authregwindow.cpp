/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#include "authregwindow.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>



AuthRegWindow::AuthRegWindow(MainWindow* mainWin, QWidget *parent)
    : QWidget(parent), mainWin(mainWin)
{

    setWindowTitle("Авторизация / Регистрация");
    lineEditLogin = new QLineEdit(this);
    lineEditLogin->setPlaceholderText("Логин");

    lineEditPassword = new QLineEdit(this);
    lineEditPassword->setPlaceholderText("Пароль");
    lineEditPassword->setEchoMode(QLineEdit::Password);

    pushButtonAuth = new QPushButton("Войти",this);
    pushButtonReg = new QPushButton("Зарегестрироваться",this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(lineEditLogin);
    layout->addWidget(lineEditPassword);
    layout->addWidget(pushButtonAuth);
    layout->addWidget(pushButtonReg);

    setLayout(layout);

    connect(pushButtonAuth,&QPushButton::clicked,this,&AuthRegWindow::onAuthClicked);
    connect(pushButtonReg,&QPushButton::clicked,this,&AuthRegWindow::onRegClicked);


}

AuthRegWindow::~AuthRegWindow()
{
}

void AuthRegWindow::onAuthClicked()
{
    QString login = lineEditLogin->text();
    QString password = lineEditPassword->text();


    bool auth = Authenticator.loginStudent(login, password);

    if (auth) {
        QMessageBox::information(this, "Авторизауция", "Успешно!");
        emit authSuccess();

    }
    else {
        QMessageBox::warning(this, "Авторизация", "Не удалось войти.");
    }

}

void AuthRegWindow::onRegClicked()
{
    QString login = lineEditLogin->text();
    QString password = lineEditPassword->text();

    bool reg = Authenticator.registerStudent(login, password);


    if (reg) {
        QMessageBox::information(this, "Регистрация", "Успешно!");
        emit authSuccess();

    } else {
        QMessageBox::warning(this, "Регистрация", "Не удалось зарегистрироваться. Или Логин уже занят");
    }
}
