#ifndef EXTRADATA_H
#define EXTRADATA_H

#include <QString>
#include <QDate>
#include "Data.h"

class ExtraData : public Data
{
private:
    QString inn;
    QString snils;
    QString schoolName;
    QDate graduationYear;
    QString universityName;
    QDate universityGraduation;

public:
    ExtraData(const QString& inn,
              const QString& snils,
              const QString& schoolName,
              const QDate& graduationYear,
              const QString& universityName,
              const QDate& universityGraduation);

};

#endif // EXTRADATA_H
