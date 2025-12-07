#include "addwork.h"
#include "ui_addwork.h"
#include"assignmentplanner.h"
#include"../JsonKeys.h"
AddWork::AddWork(PriviewWorks *p, AssignmentPlanner *planner, QWidget *parent)
    : QDialog(parent)
    , planner_(planner)
    , parser(std::make_unique<ParserJson>())
    , ui(new Ui::AddWork)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);


    connect(this,&AddWork::accepted,this,[this](){
        this->createWork();

    });



    QObject::connect(p, &PriviewWorks::Priview,this,&AddWork::onPriviewReceived);

    //QObject::connect(p,&PriviewWorks::destroyed,p,&PriviewWorks::deleteLater);

    QObject::connect(this,&AddWork::rejected,this,[this,p]()
    {
        planner_->show();
        this->close();
    });

}

AddWork::~AddWork()
{
    delete ui;

}


void AddWork::onPriviewReceived(const QJsonObject& obj)
{
    Task task = parser->UploadWork(obj);

    setWork(task.nameT, task.descT, task.dateT, task.timeT, task.priorityT);

}


void AddWork::createWork()
{
    path_ =     Planner::Works;
    name_ =     ui->lineEditName->text();
    desc_ =     ui->lineEditDesc->text();
    date_ =       ui->calendarWidget->selectedDate();
    time_ =       ui->timeEdit->time();
    priority_ = ui->comboBoxPriority->currentText();

    parser->parseWork(name_,desc_,date_,time_,priority_,path_);
    //emit CreteatedWork();

    this->close();
    planner_->show();
}

void AddWork::setWork(const QString& name,const QString& desc,const QDate& date,const QTime& time,const QString& priority)
{
    qDebug() << "1";

    ui->lineEditName->setText(name);
    ui->lineEditDesc->setText(desc);
    ui->calendarWidget->setSelectedDate(date);
    ui->timeEdit->setTime(time);
    ui->comboBoxPriority->setCurrentText(priority);

    name_ = name;
    desc_ = desc;
    date_ = date;
    time_ = time;
    priority_ = priority;


}
