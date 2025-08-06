#include "accountingassessments.h"
#include "ui_accountingassessments.h"
#include"StudentDataHandler.h"
#include<memory>
#include"academicrecordwindow.h"
#include"mainwindow.h"


accountingassessments::accountingassessments(MainWindow* mainWindow,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::accountingassessments)
    , backWindow(mainWindow)
{
    ui->setupUi(this);

    obj= std::make_unique<ImportSaveData>();


    connect(ui->btnSave,&QPushButton::clicked,this,[=](){
        obj->saveConfig(this);

    });
    connect(ui->btnBack,&QPushButton::clicked,this,&accountingassessments::Back);

}
void accountingassessments::Back()
{
    this->close();

    backWindow->show();


}
accountingassessments::~accountingassessments()
{
    delete ui;
}
