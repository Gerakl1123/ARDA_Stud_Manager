#include "coursework.h"
#include "ui_coursework.h"
#include"IODataHandler.h"
#include"mainwindow.h"
#include"JsonKeys.h"
#include"Validator.h"
#include<QPrinter>
#include<QPrintDialog>
#include<QPainter>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QByteArray>
#include"FileChooicer.h"
#include<QAction>
#include<QMenu>
#include<QMenuBar>
#include<QWidgetAction>
#include"confrimdialog.h"

Coursework::Coursework(MainWindow* mainWin, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Coursework)
    , main(mainWin)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setWindowIcon(QIcon("C:/Users/Gera/Documents/ARDA/Course.png"));
    isd = std::make_unique<ImportSaveData>();
    ser = std::make_unique<SerializerData>();
    fileManager = std::make_unique<FileManager>(this);


    ser->DataSerelizationCourse(ui->tableWidget,this);
    ui->lineEditFind->setPlaceholderText("Поиск по имени...");

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


    connect(ui->btnAdd,&QPushButton::clicked,this,&Coursework::addRow);
    connect(ui->btnBack,&QPushButton::clicked,this,&Coursework::BackMenu);
    connect(ui->btnSave,&QPushButton::clicked,this,[=](){
        isd->saveToJsonCourseWork(ui->tableWidget,this);
    });
    connect(ui->btnUpload,&QPushButton::clicked,this,[=]()
            {
        isd->loadFromCourseWork(ui->tableWidget,this);
    });
    connect(ui->btnPrinter,&QPushButton::clicked,this,&Coursework::PrinterData);
    connect(ui->bntDelete,&QPushButton::clicked,this,&Coursework::DeleteRow);
    connect(ui->btnClear,&QPushButton::clicked,this,&Coursework::ClearTable);
    connect(ui->lineEditFind,&QLineEdit::textChanged,this,&Coursework::findName);

    connect(OnOffSerelization,&QCheckBox::checkStateChanged,this,[=](int state){
        if(state == Qt::Checked)
        {
            ser->DataSerelizationCourse(ui->tableWidget,this);
        }
    });
}

Coursework::~Coursework()
{
    delete ui;
}

void Coursework::BackMenu()
{
    main->show();
    this->close();
}

void Coursework::PrinterData()
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
    }


    QByteArray byteArr = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(byteArr);
    QJsonArray arr = doc.array();

    QString html = "<h2 align='center'>Отчёт по Курсовой</h2>";
    html += "<table border='1' cellspacing='0' cellpadding='4' width='100%'>";
    html += "<tr><th>ID</th><th>ФИО</th><th>Зачетная книжка</th><th>Группа</th><th>Тема</th><th>Куратор/Руководитель</th><th>Этап Работы</th><th>Оценка</th><th>Дата Сдачи</th></tr>";

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
                        "</tr>")
                    .arg(ID, fio,testBook,group,Theme,Curator,Stage,grade,DateSTR);


    }


    html += "</table>";


    QTextDocument document;
    document.setHtml(html);
    document.print(&printer);

    QMessageBox::information(this, "Создано", "Pdf " + filePDF + " Создан" );


}

void Coursework::addRow()
{

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    for(int col = 0; col < ui->tableWidget->columnCount();col++)
    {
        if(col == 6)
        {
            comBox = new QComboBox(this);
            comBox->addItems(Stages::StageList);
            ui->tableWidget->setCellWidget(row,col,comBox);
        }
        if(col == 8)
        {
            DateEdit = new QDateEdit(this);
            ui->tableWidget->setCellWidget(row,col,DateEdit);
        }
        else{
             ui->tableWidget->setItem(row, col, new QTableWidgetItem(""));
        }
    }

}

void Coursework::DeleteRow()
{
    ConfrimDialog dlg(this);
    if(confirmCheckBox->checkState() == Qt::Checked)
    {
        if(dlg.exec() == QDialog::Accepted)
        {

            int select = ui->tableWidget->currentRow();
            if(!(select > ui->tableWidget->rowCount() || select <0))
            {
                ui->tableWidget->removeRow(select);
            }

        }
        else
        {
            QMessageBox::warning(this,"Error", " Не выбрана строка для удаления или она некорректная");
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

void Coursework::ClearTable()
{
    ConfrimDialog dlg(this);
    if(confirmCheckBox->checkState() == Qt::Checked)
    {
        if(dlg.exec() == QDialog::Accepted)
        {
            if(ui->tableWidget->rowCount() > 0)
            {
            ui->tableWidget->setRowCount(0);
            }else
            {
                return;
            }
        }

    }
    else
    {
        if(ui->tableWidget->rowCount() > 0)
        {
            ui->tableWidget->setRowCount(0);
        }else
        {
            return;
        }

    }
}


void Coursework::findName(const QString &name)
{
    ui->tableWidget->clearSelection();

    bool found = false;
    for(int i =0; i<ui->tableWidget->rowCount();i++)
    {
        for(int j =0; j<ui->tableWidget->columnCount();j++)
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

    if(!found)
    {
        QMessageBox::warning(this,"Поиск", "Нечего не найдено");
    }

    return;
}
