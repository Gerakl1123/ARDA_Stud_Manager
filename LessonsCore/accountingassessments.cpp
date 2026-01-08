#include "accountingassessments.h"
#include "ui_accountingassessments.h"
#include "../IOCore/IODataHandler.h"
#include <memory>
#include "academicrecordwindow.h"
#include "../mainwindow.h"
#include "../confrimdialog.h"
#include "../Serializer.h"
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
#include <QInputDialog>
#include "../JsonKeys.h"

accountingassessments::accountingassessments(MainWindow* mainWindow,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::accountingassessments)
    , backWindow(mainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    obj= std::make_unique<ImportSaveData>();
    dbHandler = std::make_unique<IODataBaseHandler>();
    ser = std::make_unique<SerializerData>();
    fileManager = new FileManager(this);
    tabManager = std::make_unique<TableManager>(ui->tableWidget,this);


    QSettings settings(SerelizationData::ORG_NAME,"Lesson");


    setWindowTitle("Учет Оценок");


    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *More = new QMenu("Прочее", menuBar);
    QAction* SetItem = new QAction("Перейти к ячейки", More);

    QMenu *Function = new QMenu("Функционал", menuBar);
    SaveJSON = new QAction("Сохранить в Json", More);
    UploadJSON = new QAction("Выгрузить из JSON", More);
    SaveDB = new QAction("Сохранить в DB", More);
    UploadDB = new QAction("Выгрузить из DB", More);
    Print = new QAction("Печатать в PDF", More);
    Help = new QAction("Помощь", More);
    Quit = new QAction("Выйти", More);

    More->addAction(SetItem);
    Function->addAction(SaveJSON);
    Function->addAction(UploadJSON);
    Function->addAction(SaveDB);
    Function->addAction(UploadDB);
    Function->addAction(Print);
    Function->addAction(Quit);
    Function->addAction(Help);

    menuBar->addMenu(Function);
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
            QMessageBox::warning(this, "Ошибка", "Такая ячейки нету!!");
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

    ui->tableWidget->setHorizontalHeaderLabels(JsonKeys::headerLessons);

    ser->DataSerelizationMenuStudentRecords(ui->tableWidget,this,ModeSerelization::Lessons);

    // Десерилезация дней
    days = settings.value("count_day", 0).toInt();
    column_day = settings.value("count_column_day", 6).toInt();

    if(days){
        int totalColumns = 6 + days;
        ui->tableWidget->setColumnCount(totalColumns);

        for (int day = 1; day <= days; day++) {
            int columnIndex = 6 + day - 1;
            QString header = settings.value(QString("column_day_%1").arg(day)).toString();

            ui->tableWidget->setHorizontalHeaderItem(columnIndex, new QTableWidgetItem(header));

            qDebug() << "col " << columnIndex << " name " << header;
        }
    }
    // Конец
    setupConnections();



    connect(ui->tableWidget, &QTableWidget::itemChanged, this, [this](QTableWidgetItem* item) {
        ui->tableWidget->blockSignals(true);

        tabManager->processCellData(item);


        ui->tableWidget->blockSignals(false);

    });



}

void accountingassessments::Back()
{

    backWindow->show();
    this->close();
}

accountingassessments::~accountingassessments()
{

    obj->SaveDateWidget(ui->tableWidget);

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
// Рефакторинг сделать
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
    html += "<tr><th>ID</th><th>ФИО</th><th>Группа</th><th>Название урока</th><th>Оценки</th><th>Марки Студента</th></tr>";

    for(const QJsonValue& c : arr)
    {
        if(!c.isObject()) continue;

        QJsonObject currObj = c.toObject();



        QString id = currObj["ID"].toString();
        QString fio = currObj["ФИО"].toString();
        QString group = currObj ["Группа"].toString();
        QString lesson = currObj["Название Урока"].toString();
        QJsonArray grades = currObj["Оценки Студента"].toArray();
        QJsonArray marks = currObj["Марки Студента"].toArray();

        QStringList grade;
        QStringList mark;
        for(const auto& c : grades)
        {
            grade << c.toString();
        }
        for(const auto&c : marks)
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
                        "</tr>")
                    .arg(id, fio, group,lesson, grade.join(""),mark.join(""));
    }

    html += "</table>";

    QTextDocument document;
    document.setHtml(html);
    document.print(&printer);

    QMessageBox::information(this, "Создано", "Pdf "+filePDF + " Создан" );
}

void accountingassessments::setupConnections()
{

    ui->lineEditFindName->setPlaceholderText("Поиск по имени...");

    connect(Print,&QAction::triggered,this,&accountingassessments::Printer);

    connect(Quit,&QAction::triggered,this,&accountingassessments::Back);

    connect(ui->btnDelete,&QPushButton::clicked,this,&accountingassessments::DeleteRow);

    connect(ui->lineEditFindName, &QLineEdit::textChanged, this, &accountingassessments::Find);

    connect(ui->btnClear,&QPushButton::clicked,this,&accountingassessments::ClearTabl);


    connect(Help,&QAction::triggered,this,[=](){
        QMessageBox::information(this,"Помощь", " При случайной очистке группы или удаление строки просто перезайдите в приложение или нажмите кнопку выйти и пройдите заново в меню совет всегда включайте подтверждение когда работаете пару секунд это не пару часов:)\n"
                                                 "При работе в меню зачеты подгружаем данные с меню оценок");
    });


    connect(SaveDB,&QAction::triggered,this,[=](){
        dbHandler->saveDataLesson(ui->tableWidget,DEFAULT_TABLE_ID);
    });

    connect(UploadDB,&QAction::triggered,this,[=](){
        //dbHandler->loadDataLesson(ui->tableWidget);

        QMessageBox::information(this,"Отключено","Данная функция отключена для данного меню арда 5.0 не стабильна");
    });

    connect(SaveJSON,&QAction::triggered,this,[=](){
        obj->SaveToJson(ui->tableWidget,this);

    });

    connect(UploadJSON,&QAction::triggered,this,[=](){
        obj->loadFromFile(ui->tableWidget,this);
        //QMessageBox::information(this,"Отключено","Данная функция отключена для данного меню арда 5.0 не стабильна");

    });

    connect(ui->btnAdd,&QPushButton::clicked,this,[this]()
            {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    });


}

void accountingassessments::on_btnAddDay_clicked()
{
    ui->btnAddDay->setEnabled(false);
    QSettings settings(SerelizationData::ORG_NAME,"Lesson");

    int currentColumnCount = ui->tableWidget->columnCount();
    ui->tableWidget->setColumnCount(currentColumnCount + 1);

    QString date = QDate::currentDate().toString("dd.MM.yyyy");
    ui->tableWidget->setHorizontalHeaderItem(currentColumnCount,new QTableWidgetItem(date));

    ui->tableWidget->setItem(0, currentColumnCount,new QTableWidgetItem());

    ++days;
    ++column_day;
    settings.setValue("count_day",days);
    settings.setValue("count_column_day",column_day);
    settings.setValue(QString("column_day_%1").arg(days),date);


    ui->btnAddDay->setEnabled(true);
}

void accountingassessments::on_btnEditColmn_clicked()
{
    int selectedСol = ui->tableWidget->currentColumn();
    QDialog dialog(this);
    dialog.setWindowTitle("Выбор новой даты");

    QDateEdit *dateEdit = new QDateEdit(QDate::currentDate(), &dialog);
    dateEdit->setCalendarPopup(true);


    QPushButton *ok = new QPushButton("OK", &dialog);
    QPushButton *cancel = new QPushButton("Отмена", &dialog);


    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addStretch();
    buttons->addWidget(ok);
    buttons->addWidget(cancel);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(dateEdit);
    layout->addLayout(buttons);

    connect(ok, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancel, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QDate date = dateEdit->date();
        if(date < QDate::currentDate())
        {
            QMessageBox::information(this,"Ошибка","Прошлое уже не вернуть.");
            return;
        }
        QSettings settings(SerelizationData::ORG_NAME,"Lesson");
        settings.setValue(QString("column_day_%1").arg(days),date.toString("dd.MM.yyyy"));

        ui->tableWidget->setHorizontalHeaderItem(selectedСol, new QTableWidgetItem(date.toString("dd.MM.yyyy")));

    }

}


void accountingassessments::on_btnSet_clicked()
{

}


void accountingassessments::on_btnDeleteLastColumn_clicked()
{

    if(ui->tableWidget->columnCount()<=6) return;

    QSettings Main(SerelizationData::ORG_NAME,"Lessons");

    QSettings otherL(SerelizationData::ORG_NAME,"Lesson");
    ui->tableWidget->setColumnCount(ui->tableWidget->columnCount() - 1);
    Main.setValue("columnCount",ui->tableWidget->columnCount() - 1);
    otherL.remove(QString("column_day_%1").arg(ui->tableWidget->columnCount() - 1));
    otherL.setValue("count_column_day",ui->tableWidget->columnCount() - 1);
    otherL.setValue("count_day",--days);
    Main.sync();
    otherL.sync();
    ui->tableWidget->reset();


}

