/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"mainwindow.h"
#include <QPropertyAnimation>
#include <QMainWindow>
#include"contestwindow.h"
#include"studentdataservice.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
Ui::MainWindow *ui;
private:

    void styleMainW();
    StudentDataService* windowStudent;
    contestwindow* windowContest;
    bool StyleChoice = false;
private slots:
    void openManagerStud();
    void openContestWindow();
    void ToggleStyleApp();


};
#endif // MAINWINDOW_H
