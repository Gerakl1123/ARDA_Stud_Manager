#include "extradata.h"

// extradata.cpp
ExtraData::ExtraData(
    const QString& ID,
    const QString& snils,
    const QString& phone,
    const QString& email,
    const QString& motherInfo,
    const QString& fatherInfo,
    const QString& attestatSeries,
    const QString& attestatIssuedBy,
    const QString& attestatGraduationYear,
    bool attestatWithHonors,
    bool hasPreviousEducation,
    const QString& diplomaSeries,
    const QString& diplomaIssuedBy,
    const QString& diplomaGraduationYear,
    bool diplomaWithHonors
    ) :
    Data(ID),
    snils_(snils),
    phone_(phone),
    email_(email),
    motherInfo_(motherInfo),
    fatherInfo_(fatherInfo),
    attestatSeries_(attestatSeries),
    attestatIssuedBy_(attestatIssuedBy),
    attestatGraduationYear_(attestatGraduationYear),
    attestatWithHonors_(attestatWithHonors),
    hasPreviousEducation_(hasPreviousEducation),
    diplomaSeries_(diplomaSeries),
    diplomaIssuedBy_(diplomaIssuedBy),
    diplomaGraduationYear_(diplomaGraduationYear),
    diplomaWithHonors_(diplomaWithHonors)
{

}
QJsonObject ExtraData::toJson()
{
    QJsonObject obj = std::move(Data::toJson());

    obj["СНИЛС"] = snils_;
    obj["Номер Телефона"] = phone_;
    obj["Адрес Почты"] = email_;
    obj["Данные Мать"] = motherInfo_;
    obj["Данные Отец"] = fatherInfo_;
    obj["Серия Аттестата"] = attestatSeries_;
    obj["Выдан Аттестат"] = attestatIssuedBy_;
    obj["Год окончания школы"] = attestatGraduationYear_;
    obj["Медаль/Аттестат с отличием"] = attestatWithHonors_ ? "Есть" : "Нет";

    obj["Прошлое место оброзования"] = hasPreviousEducation_ ? "Есть" : "Нет";

    obj["Серия Диплома"] = diplomaSeries_.isEmpty() ? "-" : diplomaSeries_;
    obj["Выдан Диплом"] = diplomaIssuedBy_.isEmpty() ? "-" : diplomaIssuedBy_;
    obj["Год окончания УЗ"] = diplomaGraduationYear_.isEmpty() ? "-" : diplomaGraduationYear_ ;
    obj["Медаль/Диплом с отличием"] = diplomaWithHonors_ ? "Есть" : "Нет";



    return obj;
}

