#include "iodatabasehandler.h"
#include"../FileChooicer.h"
#include"../LogicOperation.h"
#include<QTableWidget>
#include<QHeaderView>
#include<QStandardPaths>

IODataBaseHandler::IODataBaseHandler() {

    db = QSqlDatabase::addDatabase("QSQLITE");

}

IODataBaseHandler::~IODataBaseHandler()
{
    if(db.open())
    {
        db.close();
    }
}

void IODataBaseHandler::InsertDataInDB(const QString& name,QStringList& keys,QStringList& values)
{
    if(!keys.isEmpty()){
        QString placeholders = "?" + QString(", ?").repeated(keys.size() - 1);
        QString sql = QString("INSERT INTO " + name +" (%1) VALUES (%2)")
                          .arg(keys.join(", "))
                          .arg(placeholders);

        QSqlQuery query(db);

        query.prepare(sql);

        for(const auto& val : values)
        {
            query.addBindValue(val);
        }

        if(!query.exec()) {
            qDebug() << "Ошибка вставки:" << query.lastError().text();
            qDebug() << "Query:" << query.lastQuery();
        } else {
            qDebug() << "Успешная вставка строки";
        }

    }

}

bool IODataBaseHandler::createConnectionsDB(const DatabaseTypes type, const QString& other_data_db)
{

    QString name = LogicOperation::nameFileDb(type);
    db.setDatabaseName(name + other_data_db + ".db");


    if(db.isOpen()) {
        qDebug() << "БД уже открыта";
        return true;
    }

    if (!db.open()) {
        QMessageBox::information(nullptr,"Error db","Не удалось открыть базы данных: доп данные в файле лога");
        *logger << db.lastError().text();
        return false;
    }

    if (!LogicOperation::createTableDBfromTYPE(type,db)) {
        QMessageBox::information(nullptr, "Error db",
                                 "Не удалось создать таблицу в БД");
        *logger << "Ошибка создания таблицы в БД: " + name;
        return false;
    }

    *logger << "Успешно создана БД: " + (name + other_data_db + ".db");
    return true;



}

void IODataBaseHandler::loadDataLesson(QTableWidget *table)
{
    FileManager f;
    QString path(f.ChoiceDB());

    db.setDatabaseName(path);
    if(!db.open()) {
        *logger << "Не удалось открыть БД";
        return;
    }

    *logger<< "Успешное открытие БД";
    QSqlQuery query(db);

    if(!query.exec("SELECT * FROM lessons"))
    {
        *logger<< "Ошибки обращения к таблице";
        return;
    }
    *logger<< "Успешное обращение к табилце";


    table->clearContents();
    table->setRowCount(0);
    table->setColumnCount(6);
    table->setHorizontalHeaderLabels({"ID", "ФИО", "Группа", "Название Урока", "Оценки Студента","Марки Студента"});

    int row = 0;

        while(query.next())
        {
            QString ID = query.value(JsonKeys::ID).toString();
            QString name = query.value(JsonKeys::FIO).toString();
            QString group = query.value(JsonKeys::Group).toString();
            QString Lesson = query.value(JsonKeys::LessonName).toString();
            QString gradeStr = query.value(JsonKeys::StudentGrades).toString();
            QString marksStr = query.value(JsonKeys::MarksStudent).toString();

            table->insertRow(row);

            table->setItem(row, 0, new QTableWidgetItem(ID));
            table->setItem(row, 1, new QTableWidgetItem(name));
            table->setItem(row, 2, new QTableWidgetItem(group));
            table->setItem(row, 3, new QTableWidgetItem(Lesson));
            table->setItem(row, 4, new QTableWidgetItem(gradeStr));
            table->setItem(row, 5,new QTableWidgetItem(marksStr));
            ++row;
        }
        *logger<< "Успешная выгрузка в табилцу выгружено " +std::to_string(row) + " строки";



}

void IODataBaseHandler::loadDataAcademic(QTableWidget *table)
{
    FileManager f;
    QString path(f.ChoiceDB());

    db.setDatabaseName(path);
    if(!db.open()) {
        *logger << "Не удалось открыть БД";
        return;
    }

    *logger<< "Успешное открытие БД";
    QSqlQuery query(db);

    if(!query.exec("SELECT * FROM lessons"))
    {
        *logger<< "Ошибки обращения к таблице";
        return;
    }
    *logger<< "Успешное обращение к табилце";


    table->clearContents();
    table->setRowCount(0);
    table->setColumnCount(9);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    table->setHorizontalHeaderLabels({"ID", "ФИО", "Группа", "Зачетная книжка","Название предмета","Оценки Студента","Марки Студента","Автомат","Оценка за зачет"});

    int row = 0;

    while(query.next())
    {
        QString ID = query.value(JsonKeys::ID).toString();
        QString name = query.value(JsonKeys::FIO).toString();
        QString group = query.value(JsonKeys::Group).toString();
        QString Lesson = query.value(JsonKeys::LessonName).toString();
        QString gradeStr = query.value(JsonKeys::StudentGrades).toString();
        QString marksStr = query.value(JsonKeys::MarksStudent).toString();

        table->insertRow(row);


        table->setItem(row, 0, new QTableWidgetItem(ID));
        table->setItem(row, 1, new QTableWidgetItem(name));
        table->setItem(row, 2, new QTableWidgetItem(group));
        table->setItem(row, 4, new QTableWidgetItem(Lesson));
        table->setItem(row, 5, new QTableWidgetItem(gradeStr));
        table->setItem(row, 6,new QTableWidgetItem(marksStr));

        QTableWidgetItem *checkItem = new QTableWidgetItem();
        checkItem->setFlags(checkItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        checkItem->setCheckState(Qt::Unchecked);
        table->setItem(row, 7, checkItem);

        ++row;
    }
    *logger<< "Успешная выгрузка в табилцу выгружено " + std::to_string(row) + " строки";



}
void IODataBaseHandler::saveDataLesson(QTableWidget *table,const QString& other)
{
    createConnectionsDB(DatabaseTypes::LESSON,other);

    for(int row = 0; row < table->rowCount(); ++row)
    {
        QStringList keys, values;

        for(int col = 0; col < 6; ++col)
        {
            QTableWidgetItem* item = table->item(row, col);
            if(!item || item->text().isEmpty()) continue;

            QString key = table->horizontalHeaderItem(col)->text();
            QString value = item->text();
            keys << "\"" + key + "\"";
            values << value;
        }

        InsertDataInDB("lessons",keys,values);

    }
}

void IODataBaseHandler::saveDataAcademic(QTableWidget *table, const QString &other)
{
    createConnectionsDB(DatabaseTypes::ACADEMIC,other);

    for(int row = 0; row < table->rowCount(); ++row)
    {
        QStringList keys, values;

        for(int col = 0; col < table->columnCount(); ++col)
        {
            QTableWidgetItem* item = table->item(row, col);
            if(!item) continue;

            QString key = table->horizontalHeaderItem(col)->text();
            QString value = item->text();
            keys << "\"" + key + "\"";

            if(key == JsonKeys::Auto)
            {


                if (item->checkState() == Qt::Checked) {
                    values << "Ecть";
                }else
                {

                    values << "Нет";
                }

            }else{
            values << value;
            }
        }

        InsertDataInDB("academic",keys,values);

    }
}


