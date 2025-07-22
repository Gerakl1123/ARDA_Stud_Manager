#include "contestwindow.h"
#include "ui_contestwindow.h"
#include"mainwindow.h"
contestwindow::contestwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::contestwindow)
{
    ui->setupUi(this);
    contestCurrentLine = new QLineEdit;

    setWindowTitle("ContestMenu");

    if(!main)
    {
        main = std::make_unique<MainWindow>();
    }
    \
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
        "📘 <b>Конкурсы:</b><br>"
        "- Sportakiada<br>"
        "- certificate<br>"
        "- Hackathon<br><br>"
        "📄 <b>Конкурс Аттестатов:</b><br>"
        "Для использования этого меню вы должны иметь готовый файл со студентами в формате:<br>"
        "<i>Имя Балл</i>";

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
    main->show();
    this->close();

}
