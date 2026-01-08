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
#include"ContestCore/contestwindow.h"
#include "StudentManagerCore/studentdataservice.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include"admin.h"
#include"clearcash.h"
#include"FileManagerCore/filemanagerdialog.h"
#include"NotificationCORE/assignmentplanner.h"
#include"dataeditor.h"
class academicrecordwindow;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE



#include <QMainWindow>
#include <QPointer>
#include <QPalette>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QSet<qint64> NotificationChatsIDTG;
    QVector<Task> tasks;
    void setChats(const QSet<qint64> &chats);
    void setTasks(const QVector<Task>& task);

private:
    Ui::MainWindow *ui;

    void setupMenu();
    void setupConnections();

    void checkForUpdates();

    void showAboutDialog();

    void openLessons();
    void openManagerStud();
    void openContestWindow();
    void openADMINPANEL();
    void openFileManger();
    void openTextEditor();
    void openDoc();
    void openAssigmentPlanner();
    void openEditorData();

private slots:
    void onUpdateAvailable(const QString &ver);
    void onNoUpdate();
    void onNetworkError(const QString &err);

    void TelegrammNotifications();
};

#endif // MAINWINDOW_H
