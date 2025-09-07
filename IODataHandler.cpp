#include"IODataHandler.h"
#include<QFile>
#include<QLineEdit>
#include<QList>
#include"Validator.h"
#include<QMessageBox>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include"LogicOperation.h"
#include<QHeaderView>
#include<QComboBox>
#include<QDateEdit>
#include"JsonKeys.h"
#include<QPointer>
#include<algorithm>

void ImportSaveData::loadFromFile(QTableWidget* t,QWidget* p)
{
    fileManager  = std::make_unique<FileManager>(p);

    QFile file(fileManager->chooseFileJson());

    try
    {
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Error",e.what());
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument mainDoc = QJsonDocument::fromJson(data);
    QJsonArray dataArray = mainDoc.array();

    t->clearContents();
    t->setRowCount(0);
    t->setColumnCount(5);
    t->setHorizontalHeaderLabels({"ID", "ФИО", "Группа", "Название Урока", "Оценки Студента"});

    for(const auto& c : dataArray)
    {
        if (!c.isObject()) continue;

        QJsonObject obj = c.toObject();

        int row = t->rowCount();
        t->insertRow(row);

        QString ID = obj[JsonKeys::ID].toString();
        QString name = obj[JsonKeys::FIO].toString();
        QString group = obj[JsonKeys::Group].toString();
        QString Lesson = obj[JsonKeys::LessonName].toString();
        QJsonArray grades = obj[JsonKeys::StudentGrades].toArray();

        QStringList gradeList;

        for(const auto& g : grades)
        {
            gradeList<<QString::number(g.toInt());
        }

        QString gradeStr = gradeList.join(", ");
        t->setItem(row, 0, new QTableWidgetItem(ID));
        t->setItem(row, 1, new QTableWidgetItem(name));
        t->setItem(row, 2, new QTableWidgetItem(group));
        t->setItem(row, 3, new QTableWidgetItem(Lesson));
        t->setItem(row, 4, new QTableWidgetItem(gradeStr));


    }


}

void ImportSaveData::SaveToJson(QTableWidget *table,QWidget *parent)
{
    fileManager = std::make_unique<FileManager>(parent);

    QFile file(fileManager->saveFile());

    try
    {
        Validator::isFileValid(file,ModeValidator::WriteFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(parent,"Ошибка открытие файла на запись",e.what());
        return;
    }

    QJsonArray mainArray;


    for(int i = 0;i<table->rowCount();i++)
    {
        QJsonObject currOBJ;
        QJsonArray grades;

        for(int j=0;j<table->columnCount();j++)
        {
            QTableWidgetItem* item = table->item(i,j);

            QString key =table->horizontalHeaderItem(j)->text();
            QString value = item->text();

            bool ok = false;

            int intValue = value.toInt(&ok);

            if (ok && key == JsonKeys::StudentGrades)
            {
                grades.append(intValue);
            }
            else
            {
                currOBJ[key] = value;
            }


        }
        currOBJ[JsonKeys::StudentGrades] = grades;
        mainArray.append(currOBJ);
    }

    QJsonDocument docMain(mainArray);
    file.write(docMain.toJson());
    file.close();

}

void ImportSaveData::loadFromRecordBook(QTableWidget *table, QWidget *p){
    fileManager  = std::make_unique<FileManager>(p);

    QString path = fileManager->chooseFileJson();

    QFile file(path);

    try
    {
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Error file", e.what());
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument mainDoc = QJsonDocument::fromJson(data);
    QJsonArray arr = mainDoc.array();


    table->clearContents();
    table->setRowCount(0);
    table->setColumnCount(8);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    table->setHorizontalHeaderLabels({"ID", "ФИО", "Группа", "Зачетная книжка","Название предмета","Оценки Студента","Автомат","Оценка за зачет"});

    int row = 0;
    table->setRowCount(arr.size());

    for(const auto c : arr)
    {
        if(!c.isObject()) continue;

        QJsonObject obj = c.toObject();

        QString ID =obj[JsonKeys::ID].toString();
        QString fio = obj[JsonKeys::FIO].toString();
        QString group = obj[JsonKeys::Group].toString();
        QString Lesson = obj[JsonKeys::LessonName].toString();
        QJsonArray grades = obj[JsonKeys::StudentGrades].toArray();

        QList<int> gradeNumbers;
        QString gradeStr;


        for(int i=0;i<grades.size();i++)
        {

            int val = grades[i].toInt();
            gradeNumbers.append(val);

            if(i>0) gradeStr+= ", ";

             gradeStr += QString::number(val);

        }


        table->setItem(row, 0, new QTableWidgetItem(ID));
        table->setItem(row, 1, new QTableWidgetItem(fio));
        table->setItem(row, 2, new QTableWidgetItem(group));
        table->setItem(row, 4, new QTableWidgetItem(Lesson));
        table->setItem(row, 5, new QTableWidgetItem(gradeStr));

        QTableWidgetItem *checkItem = new QTableWidgetItem();
        checkItem->setFlags(checkItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        checkItem->setCheckState(Qt::Unchecked);
        table->setItem(row, 6, checkItem);




        ++row;
    }


}

void ImportSaveData::saveToJSonRecordBook(QTableWidget *table, QWidget *p)
{
    fileManager = std::make_unique<FileManager>(p);

    QFile file(fileManager->saveFile());

    try
    {
        Validator::isFileValid(file,ModeValidator::WriteFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Error",e.what());
        return;
    }

    QJsonArray main;


    for(int i = 0; i<table->rowCount(); i++)
    {
        QJsonObject currObj;
        QJsonArray grades;

        for(int j = 0; j<table->columnCount(); j++)
        {
            QTableWidgetItem* currItem = table->item(i,j);

            QString key  = table->horizontalHeaderItem(j)->text();
            QString val  = currItem ? currItem->text() : "";

                size_t autoColIndex = -1;

                if(table->horizontalHeaderItem(j)->text() == JsonKeys::Auto)
                {
                    autoColIndex = j;
                }





            bool ok = false;

            int intValue = val.toInt(&ok);

            if(ok && (key == JsonKeys::StudentGrades))
            {
                grades.append(val);
            }
            else if(key == JsonKeys::Auto)
            {

                auto* autoItem = table->item(i, autoColIndex);

                if (autoItem && autoItem->checkState() == Qt::Checked) {
                    currObj[key] = "Есть";
                }else
                {

                    currObj[key] = "Нет";
                }


            }
            else{
                currObj[key] = val;
            }

        }
        currObj[JsonKeys::StudentGrades] = grades;
        main.append(currObj);

    }

    QJsonDocument doc(main);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();


}

void ImportSaveData::saveToJsonProject(QTableWidget *table, QWidget *p)
{

    fileManager = std::make_unique<FileManager>(p);
    QFile file(fileManager->saveFile());
    try
    {
        Validator::isFileValid(file,ModeValidator::WriteFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Eror",e.what());
    }

    QJsonArray mainArr;

    for(int row = 0; row < table->rowCount();row++)
    {

        QJsonObject currObject;
        for(int col = 0; col < table->columnCount();col++)
        {
            QTableWidgetItem* item = table->item(row,col);
            QString value;
            QString key = table->horizontalHeaderItem(col)->text();
            if(!item) continue;

            value = item->text();

            /*bool ok = false;
            int valInt = value.toInt(&ok);

            if(ok && key == "Оценка")
            {
                currObject[key] = valInt;

            }*/

                currObject[key] = value;


        }
        mainArr.append(currObject);
    }

    QJsonDocument doc(mainArr);
    file.write(doc.toJson());
    file.close();
}

void ImportSaveData::loadFromProject(QTableWidget *table, QWidget *p)
{
    fileManager =  std::make_unique<FileManager>(p);

    QFile file(fileManager->chooseFileJson());

    try
    {
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Error",e.what());
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray mainArr = doc.array();


    table->clearContents();
    table->setRowCount(0);
    table->setColumnCount(6);
    table->setHorizontalHeaderLabels({"ID","ФИО","Группа","Зачетная книжка","Название Проекта","Оценка"});

    for(const auto& c : mainArr)
    {
        if(!c.isObject()) continue;

        QJsonObject obj = c.toObject();

        int row = table->rowCount();
        table->insertRow(row);

        QString ID =obj[JsonKeys::ID].toString();
        QString fio =obj[JsonKeys::FIO].toString();
        QString group =obj[JsonKeys::Group].toString();
        QString testBook =obj[JsonKeys::TestBook].toString();
        QString nameProject =obj[JsonKeys::ProjectName].toString();
        QString grade = obj[JsonKeys::Grade].toString();


        table->setItem(row,0,new QTableWidgetItem(ID));
        table->setItem(row,1,new QTableWidgetItem(fio));
        table->setItem(row,2,new QTableWidgetItem(group));
        table->setItem(row,3,new QTableWidgetItem(testBook));
        table->setItem(row,4,new QTableWidgetItem(nameProject));
        table->setItem(row,5,new QTableWidgetItem(grade));


    }



}

void ImportSaveData::saveToJsonCourseWork(QTableWidget *table, QWidget *p)
{

    fileManager = std::make_unique<FileManager>(p);
    QFile file(fileManager->saveFile());

    try
    {
        Validator::isFileValid(file,ModeValidator::WriteFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Error",e.what());
    }

    QJsonArray arr;

    for (int i = 0; i < table->rowCount(); ++i)
    {
        QJsonObject obj;

        for (int j = 0; j < table->columnCount(); ++j)
        {
            QString key = table->horizontalHeaderItem(j)->text();
            QString val;

            QTableWidgetItem* item = table->item(i, j);
            QWidget* widget = table->cellWidget(i, j);

            if (auto combo = qobject_cast<QComboBox*>(widget)) {
                val = combo->currentText();
            }
            else if (auto dateEdit = qobject_cast<QDateEdit*>(widget)) {
                val = dateEdit->date().toString("dd.MM.yyyy");
            }
            else {
                if (item) {

                    val = item->text();

                }
            }

            obj[key] = val;

        }

        arr.append(obj);
    }

    QJsonDocument doc(arr);
    file.write(doc.toJson());
    file.close();


}

void ImportSaveData::loadFromCourseWork(QTableWidget *table, QWidget *p)
{
    fileManager = std::make_unique<FileManager>(p);

    QFile file(fileManager->chooseFileJson());

    try
    {
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Error",e.what());
    }


    QByteArray byteArr = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(byteArr);
    QJsonArray arr = doc.array();

    table->clearContents();
    table->setRowCount(0);
    table->setColumnCount(9);
    table->setHorizontalHeaderLabels({"ID","ФИО","Зачетная книжка","Группа","Тема","Куратор/Руководитель","Этап Работы","Оценка","Дата Сдачи"});


    for(const auto& c : arr)
    {
        if(!c.isObject()) continue;

        QJsonObject obj = c.toObject();


        int row = table->rowCount();
        table->insertRow(row);


        QString ID = obj[JsonKeys::ID].toString();
        QString fio = obj[JsonKeys::FIO].toString();
        QString group = obj[JsonKeys::Group].toString();
        QString testBook = obj[JsonKeys::TestBook].toString();
        QString grade = obj[JsonKeys::Grade].toString();
        QString Theme = obj[JsonKeys::Theme].toString();
        QString Curator = obj[JsonKeys::Curator].toString();
        QString DateSTR = obj[JsonKeys::Date].toString();
        QString Stage = obj[JsonKeys::StageWork].toString();



        table->setItem(row,0,new QTableWidgetItem(ID));
        table->setItem(row,1,new QTableWidgetItem(fio));
        table->setItem(row,2,new QTableWidgetItem(testBook));
        table->setItem(row,3,new QTableWidgetItem(group));
        table->setItem(row,4,new QTableWidgetItem(Theme));
        table->setItem(row,5,new QTableWidgetItem(Curator));
        //==========================
        QComboBox* QCB = new QComboBox(p);
        QCB->addItems(Stages::StageList);
        QCB->setCurrentText(Stage);

        table->setCellWidget(row,6,QCB);
        // auto it = std::find(Stages::StageList.begin(),Stages::StageList.end(),Stage);

        // if(it!= Stages::StageList.end())
        // {
        //     size_t index = std::distance(Stages::StageList.begin(),it);
        //     QCB->setCurrentIndex(index);
        //    table->setCellWidget(row,6,QCB);
        // }

        //===========================

        table->setItem(row,7,new QTableWidgetItem(grade));
        //
        QDateEdit* dateEdit = new QDateEdit(p);
        QDate date = QDate::fromString(DateSTR,"dd.MM.yyyy");

        if(date.isValid())
        {
            dateEdit->setDate(date);
        }else
        {
            QDate DateBug = QDate::fromString("09.09.1999", "dd.MM.yyyy");

            dateEdit->setDate(DateBug);
            dateEdit->setToolTip("Последний баг был найден в этой дате... А если серьезно чувак... проверь свой JSON объект...");
        }

        dateEdit->setDisplayFormat("dd.MM.yyyy");
        table->setCellWidget(row, 8, dateEdit);

    }


}

void ImportSaveData::saveToJsonDiploma(QTableWidget *table, QWidget *p)
{
    fileManager = std::make_unique<FileManager>(p);
    QFile file(fileManager->saveFile());

    try
    {
        Validator::isFileValid(file,ModeValidator::WriteFile);
    }catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Error",e.what());
    }

    QJsonArray arr;

    for(int row = 0; row < table->rowCount(); ++row)
    {
        QJsonObject obj;

        for(int col = 0; col < table->columnCount(); ++col)
        {
            QString key = table->horizontalHeaderItem(col)->text();
            QTableWidgetItem* item = table->item(row,col);
            QWidget* w = table->cellWidget(row,col);
            QString value;
            if(auto combo = qobject_cast<QComboBox*>(w))
            {
                value = combo->currentText();
            }
            else if(auto date = qobject_cast<QDateEdit*>(w))
            {
                value = date->date().toString("dd.MM.yyyy");
            }else
            {
                if(item)
                {
                    value = item->text();
                }
            }
            obj[key] = value;
        }
        arr.append(obj);
    }

    QJsonDocument doc(arr);
    file.write(doc.toJson());
    file.close();

}

void ImportSaveData::loadFromDiploma(QTableWidget *table, QWidget *p)
{
    fileManager = std::make_unique<FileManager>(p);

    QFile file(fileManager->chooseFileJson());

    try
    {
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Error",e.what());
    }

    QByteArray bArr = file.readAll();
    QJsonDocument  doc = QJsonDocument::fromJson(bArr);
    QJsonArray arr(doc.array());

    for(const auto& c : arr)
    {
        if(!c.isObject()) continue;

        QJsonObject obj= c.toObject();

        int row = table->rowCount();
        table->insertRow(row);

        QString ID = obj[JsonKeys::ID].toString();
        QString fio = obj[JsonKeys::FIO].toString();
        QString group = obj[JsonKeys::Group].toString();
        QString testBook = obj[JsonKeys::TestBook].toString();
        QString grade = obj[JsonKeys::Grade].toString();
        QString Theme = obj[JsonKeys::Theme].toString();
        QString Curator = obj[JsonKeys::Curator].toString();
        QString DateSTR = obj[JsonKeys::Date].toString();
        QString Stage = obj[JsonKeys::StageWork].toString();
        QString OtherData = obj[JsonKeys::OtherData].toString();


        table->setItem(row,0,new QTableWidgetItem(ID));
        table->setItem(row,1,new QTableWidgetItem(fio));
        table->setItem(row,2,new QTableWidgetItem(testBook));
        table->setItem(row,3,new QTableWidgetItem(group));
        table->setItem(row,4,new QTableWidgetItem(Theme));
        table->setItem(row,5,new QTableWidgetItem(Curator));
        table->setItem(row,7,new QTableWidgetItem(grade));
        table->setItem(row,9,new QTableWidgetItem(OtherData));

        QComboBox* combo = new QComboBox(p);
        combo->addItems(Stages::StageListDiplom);
        combo->setCurrentText(Stage);
        table->setCellWidget(row,6,combo);

        QDate date = QDate::fromString(DateSTR, "dd.MM.yyyy");
        if(!date.isValid()){
            qDebug()<<date.toString("dd.MM.yyyy");
            date = QDate::currentDate();
        }

        QDateEdit* dateEdit = new QDateEdit(p);
        dateEdit->setDate(date);
        dateEdit->setDisplayFormat("dd.MM.yyyy");

        table->setCellWidget(row, 8, dateEdit);


    }
}

void ImportSaveData::SaveDateWidget(QTableWidget *table)
{

    if(!table) return;

    for(int row = 0; row < table->rowCount(); ++row)
    {
        for(int col = 0; col < table->columnCount(); ++col)
        {
            QMetaObject::invokeMethod(table, "cellChanged",
                                      Q_ARG(int, row),
                                      Q_ARG(int, col));
        }
    }
}
