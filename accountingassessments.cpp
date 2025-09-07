#include "accountingassessments.h"
#include "ui_accountingassessments.h"
#include"IODataHandler.h"
#include<memory>
#include"academicrecordwindow.h"
#include"mainwindow.h"
#include"confrimdialog.h"
#include"Serializer.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QTextDocument>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include<QInputDialog>

accountingassessments::accountingassessments(MainWindow* mainWindow,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::accountingassessments)
    , backWindow(mainWindow)
{
    ui->setupUi(this);

    obj= std::make_unique<ImportSaveData>();
    ser = std::make_unique<SerializerData>();
    fileManager = std::make_unique<FileManager>(this);


    setWindowIcon(QIcon("C:/Users/Gera/Desktop/JSONS/Lesson.png"));
    setWindowTitle("Учет Оценок");
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *More = new QMenu("Прочее", menuBar);
    QAction* SetItem = new QAction("Перейти к ячейки", More);
    More->addAction(SetItem);
    menuBar->addMenu(More);


    connect(SetItem,&QAction::triggered,this,[=](){
        bool ok1, ok2;
        int row = QInputDialog::getInt(this, "Перейти", "Введите строку:", 0, 0, 1024, 1, &ok1);
        if (!ok1) return;

        int col = QInputDialog::getInt(this, "Перейти", "Введите колонку:", 0, 0, 1024, 1, &ok2);
        if (!ok2) return;

        int rowCount = ui->tableWidget->rowCount();
        int colCount = ui->tableWidget->columnCount();

        if (row < 0 || row >= rowCount || col < 0 || col >= colCount) {
            QMessageBox::warning(this, "Error", "Такая ячейки нету!!");
            return;
        }

        QTableWidgetItem* item = ui->tableWidget->item(row,col);

        if(item)
        {
            if(ok1 && ok2)
            {
                ui->tableWidget->setCurrentItem(item);

            }
        }

    });

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ser->DataSerelizationMenuStudentRecords(ui->tableWidget,this,ModeSerelization::Lessons);
setupConnections();
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

void accountingassessments::DeleteRow()
{

    if(ui->checkBoxConfrimDelete->isChecked())
    {
        ConfrimDialog dlg(this);
        if(dlg.exec() == QDialog::Accepted)
        {
            int selectedRow = ui->tableWidget->currentRow();
            if (selectedRow >= 0) {
                ui->tableWidget->removeRow(selectedRow);
            }
        }
        else
        {
            return;
        }
    }
    else
    {
        int selectedRow = ui->tableWidget->currentRow();
        if (selectedRow >= 0) {
            ui->tableWidget->removeRow(selectedRow);
        }
    }

}

void accountingassessments::Find(const QString& searchName)
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
                QString currSearch = item->text();
                if(currSearch.contains(searchName,Qt::CaseInsensitive))
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

void accountingassessments::ClearTabl()
{

    ConfrimDialog dlg(this);

    if(ui->checkBoxConfrimDelete->isChecked())
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

void accountingassessments::Printer()
{

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    QString filePDF = fileManager->saveFilePDF();
    printer.setOutputFileName(filePDF);
    printer.setPageSize(QPageSize(QPageSize::A4));

    QFile file(fileManager->chooseFileJson());
    try {
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }
    catch(const std::logic_error& e) {
        QMessageBox::warning(this,"Error",e.what());
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray arr = doc.array();

    QString html = "<h2 align='center'>Отчёт по оценкам</h2>";
    html += "<table border='1' cellspacing='0' cellpadding='4' width='100%'>";
    html += "<tr><th>ID</th><th>ФИО</th><th>Группа</th><th>Название урока</th><th>Оценки</th></tr>";

    for(const QJsonValue& c : arr)
    {
        if(!c.isObject()) continue;

        QJsonObject currObj = c.toObject();



        QString id = currObj["ID"].toString();
        QString fio = currObj["ФИО"].toString();
        QString group = currObj ["Группа"].toString();
        QString lesson = currObj["Название Урока"].toString();
        QJsonArray grades = currObj["Оценки Студентa"].toArray();
        QStringList grade;

        for(const auto& c : grades)
        {
            grade << QString::number(c.toInt());
        }


        html += QString("<tr>"
                        "<td>%1</td>"
                        "<td>%2</td>"
                        "<td>%3</td>"
                        "<td>%4</td>"
                        "<td>%5</td>"
                        "</tr>")
                    .arg(id, fio, group,lesson, grade.join(", "));
    }

    html += "</table>";

    QTextDocument document;
    document.setHtml(html);
    document.print(&printer);

    QMessageBox::information(this, "Создано", "Pdf "+filePDF + " Создан" );
}

void accountingassessments::setupConnections()
{

    connect(ui->btnSave,&QPushButton::clicked,this,[=](){
        obj->SaveToJson(ui->tableWidget,this);

    });

    connect(ui->btnInput,&QPushButton::clicked,this,[=](){
        obj->loadFromFile(ui->tableWidget,this);
    });

    connect(ui->btnAdd,&QPushButton::clicked,this, [=](){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    });

    connect(ui->btnInput,&QPushButton::clicked,this,[=](){
        obj->loadFromFile(ui->tableWidget,this);
    });


    connect(ui->btnDelete,&QPushButton::clicked,this,&accountingassessments::DeleteRow);
    ui->lineEditFindName->setPlaceholderText("Поиск по имени...");
    connect(ui->lineEditFindName, &QLineEdit::textChanged, this, &accountingassessments::Find);
    connect(ui->btnBack,&QPushButton::clicked,this,&accountingassessments::Back);
    connect(ui->btnClear,&QPushButton::clicked,this,&accountingassessments::ClearTabl);
    connect(ui->btnPrinter,&QPushButton::clicked,this,&accountingassessments::Printer);
    connect(ui->btnHelp,&QPushButton::clicked,this,[=](){
        QMessageBox::information(this,"Помощь", " При случайной очистке группы или удаление строки просто перезайдите в приложение или нажмите кнопку выйти и пройдите заново в меню совет всегда включайте подтверждение когда работаете пару секунд это не пару часов:)");
    });
}
