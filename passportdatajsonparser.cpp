#include "passportdatajsonparser.h"
#include<QFile>
#include"Validator.h"
#include<QMessageBox>
#include<QSpinBox>
#include<QCheckBox>

PassportDataJSONParser::PassportDataJSONParser() {}


void PassportDataJSONParser::SaveJsonPassport(QWidget *w)
{

    QString fileName = fileManager->saveFile();

    QFile file(fileName);


    QList<QLineEdit*> lineEdits = w->findChildren<QLineEdit*>();

    QString ID;

    ID = w->findChild<QLineEdit*>("lineEditIDPassport")->text();

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

void PassportDataJSONParser::SaveJsonExtraData(QWidget *w)
{
    QString FileName = fileManager->saveFile();

    QFile file(FileName);

    QList<QSpinBox*>  spinBoxes = w->findChildren<QSpinBox*>();
    QList<QLineEdit*> lineEdits = w->findChildren<QLineEdit*>();
    QList<QCheckBox*> checkBoxes = w->findChildren<QCheckBox*>();

    QString ID = w->findChild<QLineEdit*>("lineEditIDExtra")->text();

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

