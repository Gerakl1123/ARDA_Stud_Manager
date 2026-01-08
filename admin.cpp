#include "admin.h"
#include "ui_admin.h"
#include "mainwindow.h"
#include "findobjectjson.h"
#include"JsonKeys.h"
ADMIN::ADMIN(MainWindow* main, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ADMIN)
    , isd(std::make_unique<ImportSaveData>())
    , parser(std::make_unique<ParserJson>())
    , mainWindow(main)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    modelPassport = new QStringListModel(this);
    modelExtra = new QStringListModel(this);

    ui->listView->setModel(modelPassport);
    ui->listView_2->setModel(modelExtra);


    findObject = new FindObjectJson(this);
    connect(ui->btnPrieviewInfo,&QPushButton::clicked,this,&ADMIN::openFindObject);
    connect(ui->btnQuit,&QPushButton::clicked,this,[this](){
        this->close();
        mainWindow->show();
    });

    connect(findObject,&FindObjectJson::FillList,this,[this](){
        auto objOpt = parser->findObject(FileName_,ID_);
        if (objOpt.has_value()) {
            qDebug() << "has value";
            objectPass = objOpt.value();
           isd->loadListInformationPassport(modelPassport,this,objectPass);
        }

    });
    connect(findObject,&FindObjectJson::FillList,this,[this](){
        auto objOpt = parser->findObject(FileNameExtra_,ID_);
        if (objOpt.has_value()) {
            qDebug() << "has value";
            objectExtra = objOpt.value();
            isd->loadListInformationExtra(modelExtra,this,objectExtra);
        }

    });


}

ADMIN::~ADMIN()
{
    delete ui;
}

void ADMIN::openFindObject()
{


    connect(findObject,&FindObjectJson::getID,this,&ADMIN::SaveNumber);
    connect(findObject,&FindObjectJson::getNameFile,this,&ADMIN::SaveFileName);
    connect(findObject,&FindObjectJson::getNameFileExtra,this,&ADMIN::SaveFileNamextra);
    findObject->exec();

}

void ADMIN::SaveNumber(const QString& ID)
{
    ID_ = ID;

    qDebug() << ID_;
}

void ADMIN::SaveFileName(const QString &fileName)
{
    FileName_ = fileName;
    qDebug() << FileName_;
}

void ADMIN::SaveFileNamextra(const QString &FileName)
{
    FileNameExtra_ = FileName;

}
