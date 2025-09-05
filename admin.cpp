#include "admin.h"
#include "ui_admin.h"
#include "mainwindow.h"

ADMIN::ADMIN(MainWindow* main, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ADMIN)
    , mainWindow(main)
{
    ui->setupUi(this);
}

ADMIN::~ADMIN()
{
    delete ui;
}
