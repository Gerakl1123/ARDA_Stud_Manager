<<<<<<< HEAD
<<<<<<< HEAD
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
=======
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"mainwindow.h"

#include <QMainWindow>

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

private slots:

};
#endif // MAINWINDOW_H
>>>>>>> 7acdfd58b9ccc84905bc36da7d0a7cba70d1e82e
=======
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"mainwindow.h"

#include <QMainWindow>

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

private slots:

};
#endif // MAINWINDOW_H
>>>>>>> 7acdfd58b9ccc84905bc36da7d0a7cba70d1e82e
