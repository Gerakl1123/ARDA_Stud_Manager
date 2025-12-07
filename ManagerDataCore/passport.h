#ifndef PASSPORT_H
#define PASSPORT_H

#include "Data.h"
#include <QString>
#include <QVector>
#include <QDate>
#include<QComboBox>

class PassPort final : public Data
{
private:
    QString seria_;
    QString nomer_;
    QString kemVidan_;
    QDate dateVidachi_;
    QString codePodrazdeleniya_;

public:
    PassPort() = default;

    PassPort(const QString& ID,
             const QString& firstName,
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
             const QString& codePodrazdeleniya);


    ~PassPort() override = default;

    QJsonObject toJson() override;

};

#endif
