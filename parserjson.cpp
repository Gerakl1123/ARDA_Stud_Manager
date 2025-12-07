#include "parserjson.h"
#include<QFile>
#include"Validator.h"
#include<QMessageBox>
#include<QLineEdit>
#include<QJsonArray>
#include<QJsonDocument>
#include <QJsonObject>
#include"LogicOperation.h"
#include"NotificationCORE/addwork.h"
#include"JsonKeys.h"
#include<QSpinBox>
#include<QCheckBox>

ParserJson::ParserJson()
{
    fileManager = std::make_unique<FileManager>(nullptr);

}

QString ParserJson::ReadyDataVersion(const QString& jsonDataServer)
{

    QJsonDocument doc = QJsonDocument::fromJson(jsonDataServer.toUtf8());

    if (!doc.isObject()) {
        QMessageBox::warning(nullptr, "Error", "Не коректный json Проблема с сервером ждите исправления или напишите @NiyazyanGerman");
        return "";
    }

    QJsonObject obj = doc.object();
    QString ver = obj["version"].toString();

    return ver;
}

void ParserJson::SaveJsonPassport(QWidget *w)
{

    QString fileName = fileManager->saveFile();

    QFile file(fileName);


    QList<QLineEdit*> lineEdits = w->findChildren<QLineEdit*>();

    QString ID;

    ID = w->findChild<QLineEdit*>("lineEditID")->text();

    bool unique_ID = Validator::validIDJson(fileName,ID);


    if(unique_ID == false){
        QMessageBox::information(w,"Ошибка добавления","Ваш ID не уникален");
        return;
    }

    QJsonArray arr = LogicOperation::rewriteFile(file);

    QList<QComboBox*> comboList = w->findChildren<QComboBox*>();
    QList<QDateEdit*> dateList = w->findChildren<QDateEdit*>();

    QString firstName, middleName, lastName, gender, birthPlace, citizenship, address;
    QString seria, nomer, kemVidan, codePodrazdeleniya;
    QDate birthDate, dateVidachi;

    firstName = w->findChild<QLineEdit*>("lineEditName")->text();
    middleName = w->findChild<QLineEdit*>("lineEditMiddleName")->text();
    lastName = w->findChild<QLineEdit*>("lineEditLastName")->text();
    seria = w->findChild<QLineEdit*>("lineEditSeria")->text();
    nomer = w->findChild<QLineEdit*>("lineEditNumberPassport")->text();
    kemVidan = w->findChild<QLineEdit*>("lineEditKemVidan")->text();
    codePodrazdeleniya = w->findChild<QLineEdit*>("lineEditCodePodr")->text();
    address = w->findChild<QLineEdit*>("lineEditAddress")->text();
    birthPlace = w->findChild<QLineEdit*>("lineEditBirthPlace")->text();


    gender = w->findChild<QComboBox*>("comboBoxGender")->currentText();
    citizenship = w->findChild<QComboBox*>("comboBoxGrazdanstvo")->currentText();

    birthDate = w->findChild<QDateEdit*>("dateEditBirthDay")->date();
    dateVidachi = w->findChild<QDateEdit*>("dateEditDateVidachi")->date();


    Pass = std::make_unique<PassPort>(
        ID,firstName, middleName, lastName,
        birthDate, gender, birthPlace,
        citizenship, address, seria,
        nomer, kemVidan, dateVidachi, codePodrazdeleniya
    );




    try{
        Validator::isFileValid(file,ModeValidator::WriteFile);
    }catch(const std::logic_error& e)
    {
        QMessageBox::warning(w,"Error",e.what());
        return;
    }

    QJsonObject obj = Pass->toJson();
    arr.append(obj);

    QJsonDocument doc(arr);
    file.write(doc.toJson());
    file.close();

}

void ParserJson::SaveJsonExtraData(QWidget *w)
{
    QString FileName = fileManager->saveFile();

    QFile file(FileName);

    QList<QSpinBox*>  spinBoxes = w->findChildren<QSpinBox*>();
    QList<QLineEdit*> lineEdits = w->findChildren<QLineEdit*>();
    QList<QCheckBox*> checkBoxes = w->findChildren<QCheckBox*>();

    QString ID = w->findChild<QLineEdit*>("lineEditID")->text();

    bool unique_ID = Validator::validIDJson(FileName,ID);

    if(unique_ID == false){
        QMessageBox::information(w,"Ошибка добавления","Ваш ID не уникален");
        return;
    }

    QJsonArray arr = LogicOperation::rewriteFile(file);

    QString SNILS = w->findChild<QLineEdit*>("lineEditSNILS")->text();
    QString SerialAttestat = w->findChild<QLineEdit*>("lineEditSerialAttestat")->text();
    QString phone = w->findChild<QLineEdit*>("lineEditPhone")->text();
    QString email = w->findChild<QLineEdit*>("lineEditAdressEmail")->text();
    QString mother = w->findChild<QLineEdit*>("lineEditMother")->text();
    QString father = w->findChild<QLineEdit*>("lineEditFather")->text();
    QString attestatIssuedBy = w->findChild<QLineEdit*>("lineEditGetAtesstat")->text();
    QString diplomaSeries = w->findChild<QLineEdit*>("lineEditSerialDiploma")->text();
    QString diplomaIssuedBy = w->findChild<QLineEdit*>("lineEditGetDiploma")->text();

    QString attestatYear = w->findChild<QSpinBox*>("spinBoxYearGraduationAttestat")->text();
    QString diplomaYear = w->findChild<QSpinBox*>("spinBoxYearDiploma")->text();

    bool attestatHonors = w->findChild<QCheckBox*>("checkBoxAttestat")->isChecked();
    bool hasPreviousEdu = w->findChild<QCheckBox*>("checkBoxPreviousPlace")->isChecked();
    bool diplomaHonors = w->findChild<QCheckBox*>("checkBoxDiploma")->isChecked();

    extraData = std::make_unique<ExtraData>(
        ID,
        SNILS,
        phone,
        email,
        mother,
        father,
        SerialAttestat,
        attestatIssuedBy,
        attestatYear,
        attestatHonors,
        hasPreviousEdu,
        diplomaSeries,
        diplomaIssuedBy,
        diplomaYear,
        diplomaHonors
    );

    try{
        Validator::isFileValid(file,ModeValidator::WriteFile);
    }catch(const std::logic_error& e)
    {
        QMessageBox::warning(w,"Error",e.what());
        return;
    }

    QJsonObject obj = extraData->toJson();
    arr.append(obj);

    QJsonDocument doc(arr);
    file.write(doc.toJson());
    file.close();


}

std::optional<QJsonObject> ParserJson::findObject(const QString &filename, const QString &ID)
{
    QFile file(filename);

    QJsonObject currObj;
    try{
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }catch(const std::logic_error& e)
    {
        QMessageBox::warning(nullptr,"Error", e.what());
        return std::nullopt;
    }

    QByteArray bArr = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(bArr);

    QJsonArray arr(doc.array());

    for(const auto& c : arr)
    {
        if(!c.isObject()) continue;

        currObj = c.toObject();

        auto it = currObj.find("ID");

        if (it != currObj.end() && it.value().toString() == ID) {
            qDebug() << "it != end";
            return currObj;
        }
    }

    return std::nullopt;
}

bool ParserJson::parseWork(const QString &name, const QString &desc, const QDate &date, const QTime &time, const QString &priority, QString &path)
{
    bool result = Validator::ValidWorkData(name,date,time,priority);
    if(!result) return false;

    QFile file(path);


    QJsonArray arrayWorks = LogicOperation::rewriteFile(file);

    try
    {
        Validator::isFileValid(file,ModeValidator::WriteFile);
    }
    catch(const std::invalid_argument& e)
    {
        return false;
    }


    QJsonObject obj;

    obj["Название задачи"] = name;
    obj["Описание задачи"] = desc;
    obj["Окончание даты задачи"] = date.toString("dd.MM.yyyy");
    obj["Окончание времени задачи"] = time.toString("hh:mm");
    obj["Приоритет задачи"] = priority;

    arrayWorks.append(obj);

    QJsonDocument doc(arrayWorks);

    file.write(doc.toJson());
    file.close();

        return true;
}

Task ParserJson::UploadWork(const QJsonObject &obj)
{


    QString name = obj["Название задачи"].toString();
    QString desc = obj["Описание задачи"].toString();
    QString dateStr = obj["Окончание даты задачи"].toString();
    QString timeStr = obj["Окончание времени задачи"].toString();
    QString priority = obj["Приоритет задачи"].toString();
    QDate date = QDate::fromString(dateStr, "dd.MM.yyyy");
    QTime time = QTime::fromString(timeStr,"hh:mm");


    return Task(name,desc,date,time,priority);
}

QVector<std::tuple<QString, QDate,QTime>>& ParserJson::getInfoWorks(const QJsonArray &arr)
{
    infoList.clear();

    qDebug() << "=== ДЕБАГ PARSER ===";
    qDebug() << "Размер массива:" << arr.size();

    for(const auto& c : arr)
    {
        if(!c.isObject()) continue;

        QJsonObject obj = c.toObject();

        QString name = obj["Название задачи"].toString();
        QTime time = obj["Окончание времени задачи"].toVariant().toTime();
        QString dateStr = obj["Окончание даты задачи"].toString();
        qDebug()<< dateStr << "dateSTR";
        QDate date = QDate::fromString(dateStr,"dd.MM.yyyy");
        infoList.append({name, date, time});
    }

    qDebug() << "=== КОНЕЦ ПАРСИНГА ===";
    qDebug() << "size infoList->" << infoList.size();

    return infoList;
}

bool ParserJson::DeleteObjectInArray(int number_object)
{
    QFile file(Planner::Works);

    try
    {
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }
    catch(const std::invalid_argument& e)
    {
        return false;
    }


    QByteArray bArr = file.readAll();

    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(bArr);
    QJsonArray arr = doc.array();

    QJsonArray newArr = deleteObject(arr,number_object);

    QJsonDocument newDoc(newArr);

    try
    {
        Validator::isFileValid(file,ModeValidator::DeleteWrite);
    }
    catch(const std::invalid_argument& e)
    {
        return false;
    }


    file.write(newDoc.toJson());
    file.close();

    return true;

}

QJsonArray ParserJson::deleteObject(const QJsonArray &arr, int number_object)
{

    QJsonArray newArr;
    int local = 0;
    for(const auto& c : arr)
    {
        if(!c.isObject()) continue;

        if(local == number_object) continue;

        QJsonObject obj = c.toObject();

        newArr.append(obj);
        ++local;
    }


    return newArr;
}
