/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#ifndef AUTHREGWINDOW_H
#define AUTHREGWINDOW_H

#include"AuthUser.h"
#include"mainwindow.h"
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <memory>

class AuthRegWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AuthRegWindow(MainWindow* main,QWidget *parent = nullptr);


    ~AuthRegWindow();

private slots:
    void onAuthClicked();
    void onRegClicked();

private:
    inline static UserAuthenticator Authenticator{"Log.txt"};

    QLineEdit*   lineEditLogin;
    QLineEdit*   lineEditPassword;
    QPushButton* pushButtonAuth;
    QPushButton* pushButtonReg;

    MainWindow* mainWin;

signals:

     void authSuccess();
};

#endif // AUTHREGWINDOW_H
