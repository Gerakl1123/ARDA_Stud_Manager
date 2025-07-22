#ifndef DIALOGCONTEST_H
#define DIALOGCONTEST_H

#include <QDialog>
#include<QMessageBox>
#include"include/Contest.h"
#include"contestwindow.h"
#include<QSettings>
#include<QBoxLayout>
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
    void SerelizationDeserelization();
public:
    QString getInputText();
    void ok_Button_Click();
    qint64 OnBudget();
    QString onContest();
private slots:
    void handleAccepted();

};

#endif // DIALOGCONTEST_H
