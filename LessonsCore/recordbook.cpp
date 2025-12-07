 #include "recordbook.h"
#include "ui_recordbook.h"
#include"../mainwindow.h"
#include"../IOCore/IODataHandler.h"
#include<QItemDelegate>
#include"../confrimdialog.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QByteArray>

RecordBook::RecordBook(MainWindow* main, QWidget *parent)
    : QWidget(parent)
    , backWindow(main)
    , ui(new Ui::RecordBook)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);

    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderLabels({
        "ID", "ФИО", "Группа", "Зачетная книжка",
        "Название предмета", "Оценки Студента","Марки Студента", "Автомат", "Оценка за зачет"
    });


    setWindowIcon(QIcon("C:/Users/Gera/Desktop/JSONS/TestBook.png"));
    setWindowTitle("Зачеты Студентов");

    obj = new ImportSaveData();
    ihs = new LogicOperation();

    fileManager  = new FileManager(this);
    serilizer = std::make_unique<SerializerData>();
    dbHandler = std::make_unique<IODataBaseHandler>();
    serilizer->DataSerelizationMenuStudentRecords(ui->tableWidget,this,ModeSerelization::Records);
    setupConnections();

    connect(ui->btnAdd,&QPushButton::clicked,this,&RecordBook::addRow);
    ui->lineEditFind->setPlaceholderText("Поиск по имени...");

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


}

RecordBook::~RecordBook()
{
    delete ui;
    delete obj;
    delete ihs;
}

void RecordBook::Back()
{
    backWindow->show();
    this->close();
}


void RecordBook::AutoTest(QTableWidgetItem *checkItem)
{


    if (checkItem->column() != checkboxColumn) return;

    qDebug() << "ячейка " << checkItem->row() << checkItem->column();

    QString gradesStr = ui->tableWidget->item(checkItem->row(), 5)->text();
    QList<int> gradeNumbers;

    for(QChar c : gradesStr) {
        if(c.isDigit()){
            gradeNumbers.append(c.digitValue());
        }
    }

    auto avgOpt = ihs->handleAutoTestStudent(checkItem, gradeNumbers);

    if (avgOpt) {
        ui->tableWidget->setItem(checkItem->row(), resultColumn,new QTableWidgetItem(QString::number(*avgOpt)));
    }
}


void RecordBook::FindName()
{
    ui->tableWidget->clearSelection();
    QString name = ui->lineEditFind->text();
    bool found = false;

    for(int row = 0; row<ui->tableWidget->rowCount();++row)
    {
        for(int col = 0; col<ui->tableWidget->columnCount();++col)
        {
            QTableWidgetItem* item = ui->tableWidget->item(row,col);

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

void RecordBook::DeleteRow()
{

    ConfrimDialog dlg(this);

    if(ui->checkBoxConfrmDelete->checkState())
    {
        if(dlg.exec() == QDialog::Accepted)
        {
            int select = ui->tableWidget->currentRow();
            if(select>= 0)
            {
                ui->tableWidget->removeRow(select);
            }
        }
        else
        {
            return;
        }
    } else
    {
        int select = ui->tableWidget->currentRow();
        if(select>= 0)
        {
            ui->tableWidget->removeRow(select);
        }
    }
}

void RecordBook::ClearTable()
{

    ConfrimDialog dlg(this);

    if(ui->checkBoxConfrmDelete->checkState())
    {
        if(dlg.exec() == QDialog::Accepted)
        {
            ui->tableWidget->setRowCount(0);
        }
        else
        {
            return;
        }
    }
    else
    {

        ui->tableWidget->setRowCount(0);
    }
}

void RecordBook::addRow()
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    for(int i = 0; i < ui->tableWidget->columnCount(); i++)
    {
        if(i == 7)
        {
            QTableWidgetItem *checkItem = new QTableWidgetItem();
            checkItem->setFlags(checkItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
            checkItem->setCheckState(Qt::Unchecked);
            ui->tableWidget->setItem(row, i, checkItem);

        }
        else{
            ui->tableWidget->setItem(row, i, new QTableWidgetItem(""));
        }
    }
}

void RecordBook::PrintData()
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


    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray arr = doc.array();

    QString html = "<h2 align='center'>Отчёт</h2>";
    html += "<table border='1' cellspacing='0' cellpadding='4' width='100%'>";
    html += "<tr><th>ID</th><th>ФИО</th><th>Группа</th><th>Зачетная книжка</th><th>Название предмета</th><th>Оценка за зачет</th><th>Оценки Студента</th><th>Автомат</th><th>Марки Студента</th></tr>";


    for(const auto& c: arr)
    {
        if(!c.isObject()) continue;

        QJsonObject obj = c.toObject();

        QString id = obj["ID"].toString();
        QString fio = obj["ФИО"].toString();
        QString group = obj["Группа"].toString();
        QString testBook = obj["Зачетная книжка"].toString();
        QString nameLesson = obj["Название предмета"].toString();
        QString gradeTest = obj["Оценка за зачет"].toString();
        QJsonArray grades = obj["Оценки Студента"].toArray();
        QJsonArray marks = obj["Марки Студента"].toArray();
        QString autoTest = obj["Автомат"].toString();

        QStringList grade;
        QStringList mark;
        for(const auto& c: grades)
        {
            grade << c.toString();
        }
        for(const auto& c: marks)
        {
            mark << c.toString();
        }




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
                    .arg(id, fio, group,testBook,nameLesson, gradeTest,grade.join(""),autoTest,mark.join(""));

    }

    html += "</table>";

    QTextDocument document;
    document.setHtml(html);
    document.print(&printer);

    QMessageBox::information(this, "Создано", "Pdf "+filePDF + " Создан" );

}

void RecordBook::setupConnections()
{
    connect(ui->btnUploadDB,&QPushButton::clicked,this,[=](){
        dbHandler->loadDataAcademic(ui->tableWidget);
    });

    connect(ui->btnSaveDB,&QPushButton::clicked,this,[=]{
        dbHandler->saveDataAcademic(ui->tableWidget,"600");
    });

    connect(ui->btnInputData,&QPushButton::clicked,this,[=](){
        obj->loadFromRecordBook(ui->tableWidget,this);
    });
    connect(ui->btnSaveData,&QPushButton::clicked,this,[=](){
        obj->saveToJSonRecordBook(ui->tableWidget,this);
    });


    connect(ui->btnBack,&QPushButton::clicked,this,&RecordBook::Back);
    connect(ui->btnDelete,&QPushButton::clicked,this,&RecordBook::DeleteRow);
    connect(ui->tableWidget,&QTableWidget::itemChanged,this,&RecordBook::AutoTest);
    connect(ui->btnClear,&QPushButton::clicked,this,&RecordBook::ClearTable);
    connect(ui->lineEditFind,&QLineEdit::textChanged,this,&RecordBook::FindName);
    connect(ui->btnPrinter,&QPushButton::clicked,this,&RecordBook::PrintData);
}
