#include "diploma.h"
#include "ui_diploma.h"
#include"../mainwindow.h"
#include"../confrimdialog.h"
#include<QAction>
#include<QWidgetAction>
#include<QComboBox>
#include<QDateEdit>
#include"../JsonKeys.h"
#include<QPrinter>
#include"../Validator.h"
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>

Diploma::Diploma(MainWindow* main,QWidget *parent)
    : QWidget(parent)
    , mainWin(main)
    , ui(new Ui::Diploma)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    isd = std::make_unique<ImportSaveData>();
    ser = std::make_unique<SerializerData>();
    fileManager  = new FileManager(this);

    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *moreMenu = new QMenu("Прочее", menuBar);
    confirmCheckBox = new QCheckBox("Включить Подтверждения",this);
    OnOffSerelization = new QCheckBox("Включит Серелизацию",this);
    QWidgetAction *checkBoxAction = new QWidgetAction(moreMenu);
    QWidgetAction* checkBoxSerAction = new QWidgetAction(moreMenu);

    checkBoxAction->setDefaultWidget(confirmCheckBox);
    checkBoxSerAction->setDefaultWidget(OnOffSerelization);
    moreMenu->addAction(checkBoxAction);
    moreMenu->addAction(checkBoxSerAction);
    menuBar->addMenu(moreMenu);


    ser->DataSerelizationDiploma(ui->tableWidget,this);

    connect(ui->bntAdd,&QPushButton::clicked,this,&Diploma::addRow);
    connect(ui->btnRemove,&QPushButton::clicked,this,&Diploma::deleteRow);
    connect(ui->bntClear,&QPushButton::clicked,this,&Diploma::ClearTable);
    connect(ui->btnSave,&QPushButton::clicked,this,[=](){
        isd->SaveDateWidget(ui->tableWidget);
        isd->saveToJsonDiploma(ui->tableWidget,this);
    });
    connect(ui->btnUpload,&QPushButton::clicked,this,[=](){
        isd->loadFromDiploma(ui->tableWidget,this);
    });

    connect(ui->btnPrint,&QPushButton::clicked,this,&Diploma::PrinterData);
    connect(ui->btnQuit, &QPushButton::clicked,this,&Diploma::backMain);
    // connect(ui->btnSaveDate,&QPushButton::clicked,this,[=](){
    //     isd->SaveDateWidget(ui->tableWidget);
    // });
}




Diploma::~Diploma()
{
    delete ui;
}

void Diploma::addRow()
{

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    for(int i = row; i < ui->tableWidget->rowCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            if(j == 6)
            {
                QComboBox* combo = new QComboBox(this);
                combo->addItems(Stages::StageListDiplom);
                ui->tableWidget->setCellWidget(i,j,combo);
            }
            else if(j == 8)
            {
                QDateEdit* date = new QDateEdit(this);
                ui->tableWidget->setCellWidget(i,j,date);
            }
            else{
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(""));
            }
        }
    }
}

void Diploma::deleteRow()
{
    ConfrimDialog dlg(this);
    if(confirmCheckBox->checkState() == Qt::Checked)
    {
        if(dlg.exec() == QDialog::Accepted)
        {

            int select = ui->tableWidget->currentRow();
            if(!(select > ui->tableWidget->rowCount() || select < 0))
            {
                ui->tableWidget->removeRow(select);
            }
            else
            {
                QMessageBox::warning(this,"Error", " Не выбрана строка для удаления или она некорректная");
                return;
            }
        }
        else
        {
            return;
        }
    }
    else
    {
        int select = ui->tableWidget->currentRow();
        if(!(select > ui->tableWidget->rowCount() || select <0))
        {
            ui->tableWidget->removeRow(select);
        }
        else
        {
            QMessageBox::warning(this,"Error", " Не выбрана строка для удаления или она некорректная");
            return;
        }
    }
}

void Diploma::ClearTable()
{
    ConfrimDialog dlg(this);
    if(confirmCheckBox->checkState() == Qt::Checked)
    {
        if(dlg.exec() == QDialog::Accepted)
        {

            ui->tableWidget->setRowCount(0);
        }else
        {
            return;
        }
    }else
    {

        ui->tableWidget->setRowCount(0);
    }
}

void Diploma::PrinterData()
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
    }catch(const std::logic_error& e)
    {
        QMessageBox::critical(this,"Error",e.what());
    }

    QByteArray bArr = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(bArr);
    QJsonArray arr = doc.array();

    QString html = "<h2 align='center'>Отчёт по Диплому</h2>";
    html += "<table border='1' cellspacing='0' cellpadding='4' width='100%'>";
    html += "<tr><th>ID</th><th>ФИО</th><th>Зачетная книжка</th><th>Группа</th><th>Тема</th><th>Куратор/Руководитель</th><th>Этап Работы</th><th>Оценка</th><th>Дата Сдачи</th></tr>Доп. Данные</th></tr>";

    for(const auto& c : arr)
    {
        if(!c.isObject()) continue;
        QJsonObject obj = c.toObject();


        QString ID = obj[JsonKeys::ID].toString();
        QString fio = obj[JsonKeys::FIO].toString();
        QString group = obj[JsonKeys::Group].toString();
        QString testBook = obj[JsonKeys::TestBook].toString();
        QString grade = obj[JsonKeys::Grade].toString();
        QString Theme = obj[JsonKeys::Theme].toString();
        QString Curator = obj[JsonKeys::Curator].toString();
        QString DateSTR = obj[JsonKeys::Date].toString();
        QString Stage = obj[JsonKeys::StageWork].toString();
        QString otherData = obj[JsonKeys::OtherData].toString();

        html += QString("<tr>"
                        "<td>%1</td>"
                        "<td>%2</td>"
                        "<td>%3</td>"
                        "<td>%4</td>"
                        "<td>%5</td>"
                        "<td>%6</td>"
                        "<td>%7</td>"
                        "<td>%8</td>"
                        "<td>%9</td>"
                        "<td>%10</td>"
                        "</tr>")
                    .arg(ID, fio,testBook,group,Theme,Curator,Stage,grade,DateSTR,otherData);

    }

    html +="</table>";

    QTextDocument textDoc;
    textDoc.setHtml(html);
    textDoc.print(&printer);


    QMessageBox::information(this, "Создано", "Pdf " + filePDF + " Создан" );
}

void Diploma::backMain()
{
    isd->SaveDateWidget(ui->tableWidget);
    this->close();
    mainWin->show();
}





