#include "project.h"
#include "ui_project.h"
#include"../confrimdialog.h"
#include"../mainwindow.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QByteArray>
#include"../Validator.h"

project::project(MainWindow* main,QWidget *parent)
    : QWidget(parent)
    , mainWindow(main)
    , ui(new Ui::project)
{
    isd = std::make_unique<ImportSaveData>();
    ser = std::make_unique<SerializerData>();

    fileManager  = new FileManager(this);

    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);

    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels({"ID","ФИО","Группа","Зачетная книжка","Название Проекта","Оценка"});

    setWindowIcon(QIcon("C:/Users/Gera/Desktop/JSONS/Project.png"));
    setWindowTitle("Проекты Студентов");

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->lineEditFind->setPlaceholderText("Поиск по имени...");

    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ser->DataSerelizationMenuStudentRecords(ui->tableWidget,this,ModeSerelization::Projects);

    setupConnections();
}

project::~project()
{
    delete ui;
}


void project::DeleteRow()
{
    ConfrimDialog dlg(this);

    if(ui->checkBoxConfrimDelete->checkState())
    {
        if(dlg.exec() == QDialog::Accepted)
        {
            int select = ui->tableWidget->currentRow();
            if(select>= 0)
            {
                ui->tableWidget->removeRow(select);
            }
        }
        else{
            return;
        }
    }
    else
    {
        int select = ui->tableWidget->currentRow();
        if(select>= 0)
        {
            ui->tableWidget->removeRow(select);
        }

    }
}

void project::setupConnections()
{
    connect(ui->btnAdd,&QPushButton::clicked,this,[=](){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    });
    connect(ui->btnPrint,&QPushButton::clicked,this,&project::PrintData);
    connect(ui->btnDelete,&QPushButton::clicked,this,&project::DeleteRow);
    connect(ui->lineEditFind,&QLineEdit::textChanged,this,&project::findName);
    connect(ui->btnClear,&QPushButton::clicked,this,&project::ClearTable);
    connect(ui->bntSave,&QPushButton::clicked,this,[=](){
        isd->saveToJsonProject(ui->tableWidget,this);
    });
    connect(ui->btnUpload,&QPushButton::clicked,this,[=](){
        isd->loadFromProject(ui->tableWidget,this);
    });

    connect(ui->btnBack,&QPushButton::clicked,this,[=](){
        this->close();
        mainWindow->show();
    });
}

void project::findName()
{

    ui->tableWidget->clearSelection();
    QString name = ui->lineEditFind->text();

    bool found = false;
    for(int i = 0; i< ui->tableWidget->rowCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            QTableWidgetItem* item = ui->tableWidget->item(i,j);

            if(item)
            {
                if(item->text().contains(name,Qt::CaseInsensitive))
                {
                    found = true;
                    ui->tableWidget->setCurrentItem(item);
                    break;
                }
            }
        }
        if(found) break;
    }
    if(!found){
        QMessageBox::warning(this,"Поиск", "Нечего не найдено");
    }
}

void project::ClearTable()
{

    ConfrimDialog dlg(this);

    if(ui->checkBoxConfrimDelete->checkState() == Qt::Checked)
    {
        if(dlg.exec() == QDialog::Accepted)
        {
            ui->tableWidget->setRowCount(0);
        }else
        {
            return;
        }
    }
    else
    {
        ui->tableWidget->setRowCount(0);
    }
}

void project::PrintData()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    QString filePDF = fileManager->saveFilePDF();
    printer.setOutputFileName(filePDF);
    printer.setPageSize(QPageSize(QPageSize::A4));

    QFile file(fileManager->chooseFileJson());

    try
    {
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(this,"Error",e.what());
        return;
    }

    QByteArray byteArr = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(byteArr);
    QJsonArray arr = doc.array();

    QString html = "<h2 align='center'>Отчёт по Проектам</h2>";
    html += "<table border='1' cellspacing='0' cellpadding='4' width='100%'>";
    html += "<tr><th>ID</th><th>ФИО</th><th>Группа</th><th>Зачетная книжка</th><th>Название проекта</th><th>Оценка</th></tr>";


    for(const auto& c: arr)
    {
        if(!c.isObject()) continue;

        QJsonObject obj = c.toObject();

        QString ID = obj["ID"].toString();
        QString fio = obj["ФИО"].toString();
        QString group = obj["Группа"].toString();
        QString testBook = obj["Зачетная книжка"].toString();
        QString nameProject = obj["Название Проекта"].toString();
        QString grade = obj["Оценка"].toString();




        html += QString("<tr>"
                        "<td>%1</td>"
                        "<td>%2</td>"
                        "<td>%3</td>"
                        "<td>%4</td>"
                        "<td>%5</td>"
                        "<td>%6</td>"
                        "</tr>")
                    .arg(ID, fio, group,testBook,nameProject, grade);
    }


    html += "</table>";


    QTextDocument document;
    document.setHtml(html);
    document.print(&printer);

    QMessageBox::information(this, "Создано", "Pdf " + filePDF + " Создан" );
}
