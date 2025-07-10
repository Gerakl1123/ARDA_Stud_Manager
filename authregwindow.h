<<<<<<< HEAD
<<<<<<< HEAD
#ifndef AUTHREGWINDOW_H
#define AUTHREGWINDOW_H

#include "../include/Student.h"
#include"mainwindow.h"
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <memory>

class AuthRegWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AuthRegWindow(QWidget *parent = nullptr);


private slots:
    void onAuthClicked();
    void onRegClicked();

private:
    inline static Stud manag{"Log.txt"};

    std::unique_ptr<QLineEdit> lineEditLogin;
    std::unique_ptr<QLineEdit> lineEditPassword;
    std::unique_ptr<QPushButton> pushButtonAuth;
    std::unique_ptr<QPushButton> pushButtonReg;

    static std::unique_ptr<MainWindow> mainWin;

signals:

     void authSuccess();
};

#endif // AUTHREGWINDOW_H
=======
#ifndef AUTHREGWINDOW_H
#define AUTHREGWINDOW_H

#include "../include/Student.h"
#include"mainwindow.h"
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <memory>

class AuthRegWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AuthRegWindow(QWidget *parent = nullptr);

private slots:
    void onAuthClicked();
    void onRegClicked();

private:
    inline static Stud manag{"Log.txt"};

    std::unique_ptr<QLineEdit> lineEditLogin;
    std::unique_ptr<QLineEdit> lineEditPassword;
    std::unique_ptr<QPushButton> pushButtonAuth;
    std::unique_ptr<QPushButton> pushButtonReg;

    static std::unique_ptr<MainWindow> mainWin;

signals:

     void authSuccess();
};

#endif // AUTHREGWINDOW_H
>>>>>>> 7acdfd58b9ccc84905bc36da7d0a7cba70d1e82e
=======
#ifndef AUTHREGWINDOW_H
#define AUTHREGWINDOW_H

#include "../include/Student.h"
#include"mainwindow.h"
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <memory>

class AuthRegWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AuthRegWindow(QWidget *parent = nullptr);

private slots:
    void onAuthClicked();
    void onRegClicked();

private:
    inline static Stud manag{"Log.txt"};

    std::unique_ptr<QLineEdit> lineEditLogin;
    std::unique_ptr<QLineEdit> lineEditPassword;
    std::unique_ptr<QPushButton> pushButtonAuth;
    std::unique_ptr<QPushButton> pushButtonReg;

    static std::unique_ptr<MainWindow> mainWin;

signals:

     void authSuccess();
};

#endif // AUTHREGWINDOW_H
>>>>>>> 7acdfd58b9ccc84905bc36da7d0a7cba70d1e82e
