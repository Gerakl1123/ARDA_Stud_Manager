#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"mainwindow.h"
#include <QPropertyAnimation>
#include <QMainWindow>
#include"contestwindow.h"
#include "windowsmanagerstudent.h"

class WindowsManagerStudent;

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

private:
    Ui::MainWindow *ui;
    void styleMainW();
    std::unique_ptr<WindowsManagerStudent> windowStudent;
    std::unique_ptr<ContestWindow> windowContest;

private slots:
    void openManagerStud();
    void openContestWindow();

};
#endif // MAINWINDOW_H
