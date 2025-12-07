#include "sortstudentdialog.h"
#include "ui_sortstudentdialog.h"
#include"../builderform.h"
#include"../LogicOperation.h"
SortStudentDialog::SortStudentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SortStudentDialog)
{
    ui->setupUi(this);

    fileManager = new FileManager(this);

    SerializerData* ser = new SerializerData(this);
    connect(ui->btnOk,&QPushButton::clicked,this,&SortStudentDialog::SortStudent);
    connect(ui->btnClose,&QPushButton::clicked,this,[=](){
        this->close();
    });

    BuilderForm::setupBrowseButton(ui->btnBrowseInput,ui->lineEditInput,fileManager);
    BuilderForm::setupBrowseButton(ui->btnBrowseSave,ui->lineEditSave,fileManager);

    ser->DataSerelization(this,ModeSerelization::ManagerStudent);



}

SortStudentDialog::~SortStudentDialog()
{
    delete ui;
}

bool SortStudentDialog::SortStudent()
{
    LogicOperation l;
    QString file = ui->lineEditInput->text();
    QString fileSave = ui->lineEditSave->text();

    bool result = l.handleSortStudent(file,fileSave,this);

    return result;
}
