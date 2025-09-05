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
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include"../admin.h"
#include"../clearcash.h"

class academicrecordwindow;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

#pragma once

/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#include <QMainWindow>
#include <QPointer>
#include <QPalette>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class StudentDataService;
class contestwindow;
class academicrecordwindow;
class ADMIN;
class UpdateChecker;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    StudentDataService* windowStudent = nullptr;
    contestwindow*      windowContest = nullptr;
    academicrecordwindow* windowLesson = nullptr;
    ADMIN*              AdminPanel = nullptr;

    bool StyleChoice = false;

    void setupMenu();
    void setupConnections();

    void checkForUpdates();

    void showAboutDialog();

    void openLessons();
    void openManagerStud();
    void openContestWindow();
    void openADMINPANEL();

    void ToggleStyleApp();

private slots:
    void onUpdateAvailable(const QString &ver);
    void onNoUpdate();
    void onNetworkError(const QString &err);
};

#endif // MAINWINDOW_H
