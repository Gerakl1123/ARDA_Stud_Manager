#ifndef DIALOGCONTEST_H
#define DIALOGCONTEST_H

#include <QDialog>
#include<QMessageBox>
#include"contestwindow.h"
#include<QSettings>
#include<QBoxLayout>
#include"TopBallContest.h"
#include"AttestatContest.h"
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
    qint64 OnBudget();
    Student onContest();

private slots:
    void handleAccepted();

};

#endif // DIALOGCONTEST_H
