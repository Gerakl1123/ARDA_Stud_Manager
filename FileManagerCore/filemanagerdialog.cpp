#include "filemanagerdialog.h"
#include "ui_filemanagerdialog.h"
#include"../mainwindow.h"

filemanagerdialog::filemanagerdialog(MainWindow* main, QWidget *parent)
    : QWidget(parent)
    , mainW(main)
    , ui(new Ui::filemanagerdialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->btnBackUp,&QPushButton::clicked,this,&filemanagerdialog::openBackUp);
    connect(ui->btnManager,&QPushButton::clicked,this,&filemanagerdialog::openManager);
    connect(ui->btnAdmin,&QPushButton::clicked,this,&filemanagerdialog::openADMIN);
    connect(ui->btnQuit,&QPushButton::clicked,this,&filemanagerdialog::BackMenu);
    connect(ui->btnMove,&QPushButton::clicked,this,&filemanagerdialog::MoveMenu);
    connect(ui->addFiles,&QPushButton::clicked,this,&filemanagerdialog::ZIPMenu);
}

filemanagerdialog::~filemanagerdialog()
{
    delete ui;


}

void filemanagerdialog::openBackUp()
{
    BackUp* backUp = new BackUp(this);
    backUp->setAttribute(Qt::WA_DeleteOnClose);
    backUp->show();
    this->hide();
}

void filemanagerdialog::openManager()
{
    ManagerFS* fs = new ManagerFS(this);
    fs->setAttribute(Qt::WA_DeleteOnClose);
    fs->show();
    this->hide();
}

void filemanagerdialog::openADMIN()
{
    APFS* apfs_ = new APFS(this);
    apfs_->setAttribute(Qt::WA_DeleteOnClose);
    apfs_->show();
    this->hide();

}

void filemanagerdialog::BackMenu()
{
    this->close();
    mainW->show();
}

void filemanagerdialog::MoveMenu()
{
    MoveFile* moveFile_ = new MoveFile(this);
    moveFile_->setAttribute(Qt::WA_DeleteOnClose);
    moveFile_->show();
    this->hide();
}

void filemanagerdialog::ZIPMenu()
{
    AddedObjectFiles* zip = new AddedObjectFiles(this);
    zip->setAttribute(Qt::WA_DeleteOnClose);
    zip->show();
    this->hide();
}
