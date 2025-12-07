/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#ifndef DIALOGCONTEST_H
#define DIALOGCONTEST_H

#include <QDialog>
#include<QMessageBox>
#include"contestwindow.h"
#include<QSettings>
#include<QBoxLayout>
#include<QLayout>
#include<memory>
#include"../settingsbinder.h"
#include"../FileChooicer.h"
#include"../Serializer.h"


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
    SerializerData* serelizer ;
    FileManager* fileManager;
    QList<QPair<QLineEdit*,QPushButton*>> buttonLineEditPairs;

    void setupBrowseButton(FileManager *fileManager,QLineEdit* line, QPushButton* btn);

public:
    bool OnBudget();
    bool onMaxScore();

private slots:
    void handleAccepted();

};

#endif // DIALOGCONTEST_H
