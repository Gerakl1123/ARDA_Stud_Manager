#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QDate>

class Data
{
private:
    QString firstName;        // Имя
    QString middleName;       // Отчество
    QString lastName;         // Фамилия
    QString gender;           // Пол
    QDate birthDate;          // Дата рождения
    QString birthPlace;       // Место рождения
    QString citizenship;      // Гражданство
    QString snils;            // СНИЛС
    QString inn;              // ИНН
    QString address;          // Адрес регистрации/проживания
    QString phone;            // Телефон
    QString email;            // Email

public:
    Data(const QString& firstName,
         const QString& middleName,
         const QString& lastName,
         const QDate& birthDate,
         const QString& gender,
         const QString& birthPlace,
         const QString& citizenship,
         const QString& snils,
         const QString& inn,
         const QString& address,
         const QString& phone,
         const QString& email);

    virtual ~Data() = default;

    // можно добавить геттеры/сеттеры для доступа к полям
};

#endif // DATA_H
