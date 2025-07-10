#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"mainwindow.h"
#include <QPropertyAnimation>

#include <QMainWindow>

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
    std::unique_ptr<WindowsManagerStudent> window;


private slots:
    void openManagerStud();

};
#endif // MAINWINDOW_H
