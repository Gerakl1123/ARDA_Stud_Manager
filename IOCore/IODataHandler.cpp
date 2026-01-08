#include"IODataHandler.h"
#include<QFile>
#include<QLineEdit>
#include<QList>
#include"../Validator.h"
#include<QMessageBox>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include"../LogicOperation.h"
#include<QHeaderView>
#include<QComboBox>
#include<QDateEdit>
#include<QPointer>
#include<algorithm>
#include"../JsonKeys.h"
#include<QStringListModel>

LogicOperation operations;

void ImportSaveData::loadFromFile(QTableWidget* t,QWidget* p)
{

     QString path = fileManager.chooseFileJson();
     QFile file(path);

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
    QSettings settings(SerelizationData::ORG_NAME,"Lesson");
    //t->setColumnCount(settings.value("columnCout").toInt());

    t->setHorizontalHeaderLabels({"ID", "ФИО", "Группа", "Название Урока", "Оценки Студента","Марки Студента"});

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
        QJsonArray marks = obj[JsonKeys::MarksStudent].toArray();
        QJsonArray grades = obj[JsonKeys::StudentGrades].toArray();

        QStringList gradeList;
        QStringList marksList;

        for(const auto& g : grades)
        {
            gradeList<<g.toString();
        }
        for(const auto& m: marks)
        {
            marksList<<m.toString();
        }


        QString gradeStr = gradeList.join("");
        operations.validNums(gradeStr);
        QString marksStr = marksList.join("");
        t->setItem(row, 0, new QTableWidgetItem(ID));
        t->setItem(row, 1, new QTableWidgetItem(name));
        t->setItem(row, 2, new QTableWidgetItem(group));
        t->setItem(row, 3, new QTableWidgetItem(Lesson));
        t->setItem(row, 4, new QTableWidgetItem(gradeStr));
        t->setItem(row, 5,new QTableWidgetItem(marksStr));

    }


}

void ImportSaveData::SaveToJson(QTableWidget *table,QWidget *parent)
{


    QFile file(fileManager.saveFile());


    QJsonArray mainArray;

    try
    {
        Validator::isFileValid(file,ModeValidator::DeleteWrite);
        file.close();
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(parent,"Ошибка открытие файла на запись",e.what());
        return;
    }

    try
    {
        Validator::isFileValid(file,ModeValidator::WriteFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(parent,"Ошибка открытие файла на запись",e.what());
        return;
    }



    for(int i = 0; i<table->rowCount();i++)
    {
        QJsonObject currOBJ;
        QJsonArray grades;
        QJsonArray marks;
        for(int j=0; j < 6 ;j++)
        {
            QTableWidgetItem* item = table->item(i,j);


            if(!item) continue;
            QString key =table->horizontalHeaderItem(j)->text();
            QString value = item->text();

            if (key == JsonKeys::StudentGrades)
            {
                grades.append(value);
            }else if( key == JsonKeys::MarksStudent)
            {
                marks.append(value);
            }
            else
            {
                currOBJ[key] = value;
            }


        }
        currOBJ[JsonKeys::StudentGrades] = grades;
        currOBJ[JsonKeys::MarksStudent] = marks;
        mainArray.append(currOBJ);

    }

    QJsonDocument docMain(mainArray);
    file.write(docMain.toJson());
    file.close();

}

void ImportSaveData::loadFromRecordBook(QTableWidget *table, QWidget *p){


    QString path = fileManager.chooseFileJson();

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
    table->setColumnCount(9);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    table->setHorizontalHeaderLabels({"ID", "ФИО", "Группа", "Зачетная книжка","Название предмета","Оценки Студента","Марки Студента","Автомат","Оценка за зачет"});

    // int row = 0;
    // table->setRowCount(arr.size());

    for(const auto c : arr)
    {
        if(!c.isObject()) continue;

        int row = table->rowCount();
        table->insertRow(row);

        QJsonObject obj = c.toObject();

        QString ID =obj[JsonKeys::ID].toString();
        QString fio = obj[JsonKeys::FIO].toString();
        QString group = obj[JsonKeys::Group].toString();
        QString Lesson = obj[JsonKeys::LessonName].toString();
        QJsonArray grades = obj[JsonKeys::StudentGrades].toArray();
        QJsonArray marks = obj[JsonKeys::MarksStudent].toArray();

        QStringList gradeList;

        QStringList marksList;

        qDebug()<<QString::number(grades.size());
        for(const auto& g : grades)
        {
            gradeList<<g.toString();
        }
        for(const auto& m: marks)
        {
            marksList<<m.toString();
        }



        QString gradeStr = gradeList.join("");
        operations.validNums(gradeStr);
        QString marksStr = marksList.join("");
        table->setItem(row, 0, new QTableWidgetItem(ID));
        table->setItem(row, 1, new QTableWidgetItem(fio));
        table->setItem(row, 2, new QTableWidgetItem(group));
        table->setItem(row, 4, new QTableWidgetItem(Lesson));
        table->setItem(row, 5, new QTableWidgetItem(gradeStr));
        table->setItem(row, 6, new QTableWidgetItem(marksStr));

        QTableWidgetItem *checkItem = new QTableWidgetItem();
        checkItem->setFlags(checkItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        checkItem->setCheckState(Qt::Unchecked);
        table->setItem(row, 7, checkItem);

        // ++row;
    }


}

void ImportSaveData::saveToJSonRecordBook(QTableWidget *table, QWidget *p)
{


    QFile file(fileManager.saveFile());

    QJsonArray main;

    try
    {
        Validator::isFileValid(file,ModeValidator::DeleteWrite);
        file.close();
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Ошибка открытие файла на запись",e.what());
        return;
    }

    try
    {
        Validator::isFileValid(file,ModeValidator::WriteFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Error",e.what());
        return;
    }



    for(int i = 0; i<table->rowCount(); i++)
    {
        QJsonObject currObj;
        QJsonArray grades;
        QJsonArray marks;
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



            if((key == JsonKeys::StudentGrades))
            {
                grades.append(val);
            }else if(key == JsonKeys::MarksStudent)
            {
                marks.append(val);
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
        currObj[JsonKeys::MarksStudent] = marks;
        main.append(currObj);

    }

    QJsonDocument doc(main);
    file.write(doc.toJson());
    file.close();


}

void ImportSaveData::saveToJsonProject(QTableWidget *table, QWidget *p)
{



    QFile file(fileManager.saveFile());

    QJsonArray mainArr;

    try
    {
        Validator::isFileValid(file,ModeValidator::DeleteWrite);
        file.close();
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Ошибка открытие файла на запись",e.what());
        return;
    }
    try
    {
        Validator::isFileValid(file,ModeValidator::WriteFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Eror",e.what());
        return;
    }


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


    QFile file(fileManager.chooseFileJson());

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



    QFile file(fileManager.saveFile());

    QJsonArray arr ;


    try
    {
        Validator::isFileValid(file,ModeValidator::DeleteWrite);
        file.close();
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Ошибка открытие файла на запись",e.what());
        return;
    }

    try
    {
        Validator::isFileValid(file,ModeValidator::WriteFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Error",e.what());
        return;
    }


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


    QFile file(fileManager.chooseFileJson());

    try
    {
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Error",e.what());
        return;
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

    QFile file(fileManager.saveFile());

    QJsonArray arr;

    try
    {
        Validator::isFileValid(file,ModeValidator::DeleteWrite);
        file.close();
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Ошибка открытие файла на запись",e.what());
        return;
    }

    try
    {
        Validator::isFileValid(file,ModeValidator::WriteFile);
    }catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Error",e.what());
        return;
    }



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

    QFile file(fileManager.chooseFileJson());

    try
    {
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(p,"Error",e.what());
        return;
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
            QMetaObject::invokeMethod(table, "cellChanged",Q_ARG(int, row),Q_ARG(int, col));
        }
    }
}

void ImportSaveData::loadListInformationExtra(QStringListModel *model, QWidget *p, QJsonObject &obj)
{
    QString ID = obj["ID"].toString();
    QString snils = obj["СНИЛС"].toString();
    QString phone = obj["Номер Телефона"].toString();
    QString email = obj["Адрес Почты"].toString();
    QString motherInfo = obj["Данные Мать"].toString();
    QString fatherInfo = obj["Данные Отец"].toString();
    QString attestatSeries = obj["Серия Аттестата"].toString();
    QString attestatIssuedBy = obj["Выдан Аттестат"].toString();
    QString attestatGraduationYear = obj["Год окончания школы"].toString();
    QString diplomaGraduationYearStr = obj["Год окончания УЗ"].toString();
    QString diplomaGraduationYear = diplomaGraduationYearStr == "-" ? "" : diplomaGraduationYearStr;

    bool attestatWithHonors = obj["Медаль/Аттестат с отличием"].toString() == "Есть";
    bool hasPreviousEducation = obj["Прошлое место оброзования"].toString() == "Есть";
    bool diplomaWithHonors = obj["Медаль/Диплом с отличием"].toString() == "Есть";

    QString diplomaSeries = obj["Серия Диплома"].toString();
    if (diplomaSeries == "-") diplomaSeries.clear();

    QString diplomaIssuedBy = obj["Выдан Диплом"].toString();
    if (diplomaIssuedBy == "-") diplomaIssuedBy.clear();

    QStringList extraDataList{
        "ID: " + ID,
        "СНИЛС: " + snils,
        "Номер Телефона: " + phone,
        "Адрес Почты: " + email,
        "Данные Мать: " + motherInfo,
        "Данные Отец: " + fatherInfo,
        "Серия Аттестата: " + attestatSeries,
        "Выдан Аттестат: " + attestatIssuedBy,
        "Год окончания школы: " + attestatGraduationYear,
        "Медаль/Аттестат с отличием: " + QString(attestatWithHonors ? "Есть" : "Нет"),
        "Прошлое место образования: " + QString(hasPreviousEducation ? "Есть" : "Нет"),
        "Серия Диплома: " + (diplomaSeries.isEmpty() ? "-" : diplomaSeries),
        "Выдан Диплом: " + (diplomaIssuedBy.isEmpty() ? "-" : diplomaIssuedBy),
        "Год окончания УЗ: " + (diplomaGraduationYear.isEmpty() ? "-" : diplomaGraduationYear),
        "Медаль/Диплом с отличием: " + QString(diplomaWithHonors ? "Есть" : "Нет")
    };

    model->setStringList(extraDataList);
}
void ImportSaveData::loadListInformationPassport(QStringListModel *model, QWidget *p,  QJsonObject &obj)
{


    QString ID             = obj["ID"].toString();
    QString adress         = obj["Адреcс проживания"].toString();
    QString citizenship    = obj["Гражданство"].toString();
    QString issueDate      = obj["Дата выдачи"].toString();
    QString birthDate      = obj["День рождения"].toString();
    QString firstName      = obj["Имя"].toString();
    QString issuedBy       = obj["Кем выдан"].toString();
    QString departmentCode = obj["Код подразделения"].toString();
    QString birthPlace     = obj["Место рождения"].toString();
    QString passportNumber = obj["Номер пасспорта"].toString();
    QString middleName       = obj["Фамилия"].toString();
    QString lastName     = obj["Отчество"].toString();
    QString gender         = obj["Пол"].toString();
    QString passportSeries = obj["Серия пасспорта"].toString();


    QStringList data{
        "ID: " + ID,
        "Адрес проживания: " + adress,
        "Гражданство: " + citizenship,
        "Дата выдачи: " + issueDate,
        "День рождения: " + birthDate,
        "Имя: " + firstName,
        "Кем выдан: " + issuedBy,
        "Код подразделения: " + departmentCode,
        "Место рождения: " + birthPlace,
        "Номер паспорта: " + passportNumber,
        "Фамилия: " + middleName,
        "Отчество: " + lastName,
        "Пол: " + gender,
        "Серия паспорта: " + passportSeries
    };
    model->setStringList(data);

    /* int row = t->rowCount();
    // t->insertRow(row);

    // t->setItem(row, DataKeys::Columns::FirstName, new QTableWidgetItem(firstName));
    // t->setItem(row, DataKeys::Columns::MiddleName, new QTableWidgetItem(middleName));
    // t->setItem(row, DataKeys::Columns::LastName, new QTableWidgetItem(lastName));
    // t->setItem(row, DataKeys::Columns::Gender, new QTableWidgetItem(gender));
    // t->setItem(row, DataKeys::Columns::BirthPlace, new QTableWidgetItem(birthPlace));
    // t->setItem(row, DataKeys::Columns::Address, new QTableWidgetItem(address));
    // t->setItem(row, DataKeys::Columns::PassportSeries, new QTableWidgetItem(passportSeries));
    // t->setItem(row, DataKeys::Columns::PassportNumber, new QTableWidgetItem(passportNumber));
    // t->setItem(row, DataKeys::Columns::IssuedBy, new QTableWidgetItem(issuedBy));
    // t->setItem(row, DataKeys::Columns::DepartmentCode, new QTableWidgetItem(departmentCode));
    // t->setItem(row, DataKeys::Columns::Citizenship, new QTableWidgetItem(citizenship));

    // QDateEdit *wbirthDate = new QDateEdit(p);
    // QDate dateB = QDate::fromString(birthDate, "dd.MM.yyyy");
    // if (!dateB.isValid()) {
    //     qWarning() << "Некоректная дата рождения:" << birthDate;
    //     dateB = QDate::currentDate();
    // }

    // wbirthDate->setDate(dateB);
    // wbirthDate->setCalendarPopup(true);

    // wbirthDate->setReadOnly(true);

    // t->setCellWidget(row, DataKeys::Columns::BirthDate, wbirthDate);

    // QDateEdit *wIssueDate = new QDateEdit(p);
    // QDate dateIssue = QDate::fromString(issueDate, "dd.MM.yyyy");
    // if (!dateIssue.isValid()) {
    //     qWarning() << "Некоректная дата выдачи:" << issueDate;
    //     dateIssue = QDate::currentDate();
    // }
    // wIssueDate->setDate(dateIssue);
    // wIssueDate ->setEnabled(false);
    // t->setCellWidget(row, DataKeys::Columns::IssueDate, wIssueDate);
*/
}

