#include "assignmentplanner.h"
#include "ui_assignmentplanner.h"
#include"addwork.h"
#include"priviewworks.h"
#include"notificationmanager.h"
#include"../mainwindow.h"
AssignmentPlanner::AssignmentPlanner(MainWindow *qMain, QWidget *parent)
    : QWidget(parent)
    ,main_(qMain)
    , ui(new Ui::AssignmentPlanner)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);



    connect(ui->btnAdd,&QPushButton::clicked,this,&AssignmentPlanner::openAdder);
    connect(ui->btnPriview,&QPushButton::clicked,this,&AssignmentPlanner::openPriviewWorks);
    connect(ui->btnNotificationSettenings,&QPushButton::clicked,this,&AssignmentPlanner::openSettingsNotification);
    connect(ui->btnLeave,&QPushButton::clicked,this,[this](){
        this->close();
        main_->show();
    });
}

AssignmentPlanner::~AssignmentPlanner()
{
    delete ui;
}

void AssignmentPlanner::openAdder()
{
    add = new AddWork(nullptr,this,nullptr);
    add->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();

    add->show();
}

void AssignmentPlanner::openPriviewWorks()
{
    priview = new PriviewWorks(this,nullptr);
    priview->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    priview->show();
}

void AssignmentPlanner::openSettingsNotification()
{

    notific = new NotificationManager(this,nullptr);
    notific->setAttribute(Qt::WA_DeleteOnClose);
   // this->hide();
    notific->show();
}

