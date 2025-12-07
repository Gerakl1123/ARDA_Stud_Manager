#ifndef EXTRADATA_H
#define EXTRADATA_H

#include <QString>
#include <QDate>
#include "Data.h"
#include<QJsonObject>

class ExtraData : public Data
{
private:
    // Личные данные
    QString snils_;
    QString phone_;
    QString email_;

    // Данные о Родителях
    QString motherInfo_;
    QString fatherInfo_;

    // Данные об Атестате
    QString attestatSeries_;
    QString attestatIssuedBy_;
    QString attestatGraduationYear_;
    bool attestatWithHonors_ = false;


    //Данные об прошлом оброзование
    bool hasPreviousEducation_ = false;
    QString diplomaSeries_;
    QString diplomaIssuedBy_;
    QString diplomaGraduationYear_;
    bool diplomaWithHonors_ = false;

public:
    ExtraData(const QString& ID,
        const QString& snils = QString(),
        const QString& phone = QString(),
        const QString& email = QString(),
        const QString& motherInfo = QString(),
        const QString& fatherInfo = QString(),
        const QString& attestatSeries = QString(),
        const QString& attestatIssuedBy = QString(),
        const QString& attestatGraduationYear = QString(),
        bool attestatWithHonors = false,
        bool hasPreviousEducation = false,
        const QString& diplomaSeries = QString(),
        const QString& diplomaIssuedBy = QString(),
        const QString& diplomaGraduationYear = QString(),
        bool diplomaWithHonors = false
    );

    QJsonObject toJson() override;

};

#endif // EXTRADATA_H
