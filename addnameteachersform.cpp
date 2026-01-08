#include "addnameteachersform.h"
#include "ui_addnameteachersform.h"
#include"FileManagerCore/managerfs.h"

AddNameTeachersForm::AddNameTeachersForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddNameTeachersForm)
    , schedule(std::make_unique<DataSchedule>())
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);

    ManagerWorker w;
    w.CreateDir(".","Расписание");

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->pushButtonSave,&QPushButton::clicked,this,[this](){
       setNamesTeachersData(ui->lineEditName->text(),ui->lineEditMiddleName->text(),ui->lineEditLastName->text());

    });

    connect(ui->pushButtonDeleteRow,&QPushButton::clicked,this,[this](){
         if (counter == 0) return;

        int lastRow = counter - 1;
        auto* name = ui->tableWidget->item(lastRow,0);
        auto* m = ui->tableWidget->item(lastRow,1);
        auto* l = ui->tableWidget->item(lastRow,2);


        Teacher currentTeacher{name->text(), m->text(), l->text()};

        schedule->Teachers.remove(currentTeacher);

        --counter;
        ui->tableWidget->setRowCount(counter);


    });

    connect(ui->pushButtonDeleteCurrRow,&QPushButton::clicked,this,[this](){

        int curr = ui->tableWidget->currentRow();
        if (curr < 0) return;

        auto* name = ui->tableWidget->item(curr,0);
        auto* m = ui->tableWidget->item(curr,1);
        auto* l = ui->tableWidget->item(curr,2);

        Teacher currentTeacher{name->text(), m->text(), l->text()};

        schedule->Teachers.remove(currentTeacher);

        --counter;
        ui->tableWidget->removeRow(curr);

    });


    connect(ui->pushButtonGo,&QPushButton::clicked,this,[this](){
        QString file = "Расписание/teachers.json";
        bool success = jsonParser->setDataTeachers(file,schedule->Teachers);
        success ? QMessageBox::information(this,"Отправка","Успешно отправлено")
                : QMessageBox::information(this,"Отправка","Ошибка отправки");

    });

}

AddNameTeachersForm::~AddNameTeachersForm()
{
    delete ui;
}

void AddNameTeachersForm::setNamesTeachersData(const QString &name, const QString &MiddleName, const QString &LastName)
{

    if(name.isEmpty() || MiddleName.isEmpty() || LastName.isEmpty()) return;

    ui->lineEditName->setText("");
    ui->lineEditMiddleName->setText("");
    ui->lineEditLastName->setText("");

    schedule->Teachers.insert({name,MiddleName,LastName});

    QTableWidgetItem* NameItem = new QTableWidgetItem(name);
    QTableWidgetItem* MiddleItem = new QTableWidgetItem(MiddleName);
    QTableWidgetItem* LastItem = new QTableWidgetItem(LastName);

    ui->tableWidget->insertRow(counter);
    ui->tableWidget->setItem(counter,0,NameItem);
    ui->tableWidget->setItem(counter,1,MiddleItem);
    ui->tableWidget->setItem(counter,2,LastItem);


    ++counter;
}
