/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#include "contestwindow.h"
#include "ui_contestwindow.h"
#include"mainwindow.h"
contestwindow::contestwindow(MainWindow* mainWindow,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::contestwindow)
    , mainWindow_(mainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon("C:/Users/Gera/Desktop/JSONS/Contest.png"));
    setWindowTitle("Менеджер Конкурсов");


    connect(ui->pushButtonHelp, &QPushButton::clicked, this, &contestwindow::pushHelp);
    connect(ui->pushButtonCurrent,&QPushButton::clicked,this,&contestwindow::pushCurrentButton);
    connect(ui->pushButtonAttestat,&QPushButton::clicked,this,&contestwindow::pushAttestatButton);
    connect(ui->pushButtonBackMain,&QPushButton::clicked,this,&contestwindow::BackMenu);

}

contestwindow::~contestwindow()
{
    delete ui;
}

void contestwindow::pushHelp()
{

    QString helpText =
        "📘 <b>Меню запусков конкурсов:</b><br><br>"
        "Это меню предназначено для запуска различных конкурсов среди студентов, таких как:<br>"
        "🏅 <i>Конкурс на высший балл</i><br>"
        "📄 <i>Конкурс по аттестатам</i><br>"
        "🏆 <i>Спартакиада</i><br>"
        "💡 <i>Хакатон</i><br><br>"
        "📥 Для работы с конкурсами необходимо подготовить файл со студентами в формате:<br>"
        "<i>Имя Балл</i><br><br>"
        "⚙️ После загрузки данных вы сможете выбрать нужный конкурс, настроить параметры (например, количество мест, проходной балл) и запустить его.";

    QMessageBox msgBox;
    msgBox.setWindowTitle("Помощь");
    msgBox.setText(helpText);
    msgBox.setWindowIcon(QIcon("C:/Users/Gera/Documents/Student_Manager_ARDA/ico/iconInfo.png"));
    msgBox.exec();

}

void contestwindow::pushCurrentButton()
{
    DialogContest dialog(ModeCurrent, this);

    if(dialog.exec() == QDialog::Accepted)
    {
    }
}

void contestwindow::pushAttestatButton()
{
    DialogContest dialog(ModeAttestat, this);

    if(dialog.exec() == QDialog::Accepted);
}

void contestwindow::BackMenu()
{
    mainWindow_->show();
    this->close();

}
