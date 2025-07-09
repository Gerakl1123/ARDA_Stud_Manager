#include "authregwindow.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

std::unique_ptr<MainWindow> AuthRegWindow::mainWin = nullptr;


AuthRegWindow::AuthRegWindow(QWidget *parent)
    : QWidget(parent)
{

    if (!mainWin) {
        mainWin = std::make_unique<MainWindow>();
    }

    setWindowTitle("Авторизация / Регистрация");
    lineEditLogin = std::make_unique<QLineEdit>(this);
    lineEditLogin->setPlaceholderText("Логин");

    lineEditPassword = std::make_unique<QLineEdit>(this);
    lineEditPassword->setPlaceholderText("Пароль");
    lineEditPassword->setEchoMode(QLineEdit::Password);

    pushButtonAuth = std::make_unique<QPushButton>("Войти",this);
    pushButtonReg =std::make_unique<QPushButton>("Зарегестрироваться",this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(lineEditLogin.get());
    layout->addWidget(lineEditPassword.get());
    layout->addWidget(pushButtonAuth.get());
    layout->addWidget(pushButtonReg.get());

    setLayout(layout);
    connect(pushButtonAuth.get(),&QPushButton::clicked,this,&AuthRegWindow::onAuthClicked);
    connect(pushButtonReg.get(),&QPushButton::clicked,this,&AuthRegWindow::onRegClicked);


}



void AuthRegWindow::onAuthClicked()
{
    QString login = lineEditLogin->text();
    QString password = lineEditPassword->text();

    std::string loginStr = login.toStdString();
    std::string passwordStr = password.toStdString();

    bool auth = manag.loginStudent(loginStr, passwordStr);

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
    std::string loginStr = login.toStdString();
    std::string passwordStr = password.toStdString();

    bool reg = manag.registerStudent(loginStr, passwordStr);


    if (reg) {
        QMessageBox::information(this, "Регистрация", "Успешно!");
        emit authSuccess();

    } else {
        QMessageBox::warning(this, "Регистрация", "Не удалось зарегистрироваться.");
    }
}






