#include "passport.h"
#include <QJsonObject>


PassPort::PassPort(const QString &ID, const QString& firstName,
                   const QString& middleName,
                   const QString& lastName,
                   const QDate& birthDate,
                   const QString& gender,
                   const QString& birthPlace,
                   const QString& citizenship,
                   const QString& address,
                   const QString& seria,
                   const QString& nomer,
                   const QString& kemVidan,
                   const QDate& dateVidachi,
                   const QString& codePodrazdeleniya)
    : Data(ID,firstName, middleName, lastName, birthDate, gender, birthPlace, citizenship, address),
    seria_(seria),
    nomer_(nomer),
    kemVidan_(kemVidan),
    dateVidachi_(dateVidachi),
    codePodrazdeleniya_(codePodrazdeleniya)
{


}

QJsonObject PassPort::toJson()
{
   QJsonObject obj = Data::toJson();

    obj["Серия пасспорта"] = seria_;
   obj["Номер пасспорта"] = nomer_;
    obj["Кем выдан"] = kemVidan_;
   obj["Код подразделения"] = codePodrazdeleniya_;
    obj["Дата выдачи"] = dateVidachi_.toString("dd.MM.yyyy");

   return obj;

}



