#ifndef DIALOGCONTEST_H
#define DIALOGCONTEST_H

#include <QDialog>
#include<QMessageBox>
#include"include/Contest.h"
#include"contestwindow.h"

enum DialogMode{

    ModeAttestat,
    ModeCurrent
};


namespace Ui {
class DialogContest;
}

class DialogContest : public QDialog
{
    Q_OBJECT

public:
    explicit DialogContest(DialogMode mode ,QWidget *parent = nullptr);
    void setupInterface();
    ~DialogContest();

private:
    Ui::DialogContest *ui;
    DialogMode currentMode;

public:
    QString getInputText();
    void ok_Button_Click();
    qint64 OnBudget();

private slots:
    void handleAccepted();

};

#endif // DIALOGCONTEST_H
