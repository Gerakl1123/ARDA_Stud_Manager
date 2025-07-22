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
    explicit contestwindow(QWidget *parent = nullptr);
    ~contestwindow();

private:
    Ui::contestwindow *ui;
    std::unique_ptr<MainWindow> main;

    QLineEdit* contestCurrentLine;

private slots:
    void pushHelp();
    void pushCurrentButton();
    void pushAttestatButton();
    void BackMenu();


};

#endif // CONTESTWINDOW_H
