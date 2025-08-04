/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#ifndef CONTESTWINDOW_H
#define CONTESTWINDOW_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QMessageBox>
#include<QLineEdit>
#include"dialogcontest.h"

class MainWindow;

namespace Ui {
class contestwindow;
}

class contestwindow : public QWidget
{
    Q_OBJECT

public:
    explicit contestwindow(MainWindow* mainWindow, QWidget *parent = nullptr);
    ~contestwindow();

private:
    Ui::contestwindow *ui;
    MainWindow* mainWindow_;

private slots:
    void pushHelp();
    void pushCurrentButton();
    void pushAttestatButton();
    void BackMenu();


};

#endif // CONTESTWINDOW_H
