#include "Data.h"
#include<QDateEdit>
#include<QJsonObject>
#include"extradata.h"
#include"passport.h"
Data::Data(const QString &ID, const QString &firstName, const QString &middleName, const QString &lastName, const QDate &birthDate, const QString &gender, const QString &birthPlace, const QString &citizenship, const QString &address)
    : ID_(ID),firstName_(firstName),middleName_(middleName),lastName_(lastName),birthDate_(birthDate),gender_(gender),birthPlace_(birthPlace),citizenship_(citizenship),address_(address)
{

}

Data::Data(const QString &ID):
    ID_(ID){

}

QJsonObject Data::toJson()
{
    QJsonObject obj;
    if(auto* extra = dynamic_cast<ExtraData*>(this))
    {
        obj["ID"] = ID_;
    }else if(auto * pass = dynamic_cast<PassPort*>(this))
    {
        obj["ID"] = ID_;
        obj["Имя"] = firstName_;
        obj["Фамилия"] = middleName_;
        obj["Отчество"] = lastName_;
        obj["День рождения"] = birthDate_.toString("dd.MM.yyyy");
        obj["Пол"] = gender_;
        obj["Место рождения"] = birthPlace_;
        obj["Гражданство"] = citizenship_;
        obj["Адресс проживания"] = address_;
    }

    return obj;
}

QVector<QString> Data::getData() const noexcept
{
    return QVector<QString>{
        ID_,
        firstName_,
        middleName_,
        lastName_,
        birthDate_.toString("dd.MM.yyyy"),
        gender_,
        birthPlace_,
        citizenship_,
        address_
    };
}

