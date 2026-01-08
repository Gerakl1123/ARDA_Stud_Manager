#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QDate>
#include<QComboBox>
class Data
{
private:
    QString firstName_;
    QString middleName_;
    QString lastName_;
    QString gender_;
    QDate birthDate_;
    QString birthPlace_;
    QString citizenship_;
    QString address_;
    QString ID_;

protected:
    Data(const QString& ID,
         const QString& firstName,
         const QString& middleName,
         const QString& lastName,
         const QDate& birthDate,
         const QString& gender,
         const QString& birthPlace,
         const QString& citizenship,
         const QString& address
         );

    Data(const QString& ID);

    virtual ~Data() = default;

    virtual QJsonObject toJson();
    virtual QVector<QString> getData() const noexcept;

};

#endif // DATA_H
