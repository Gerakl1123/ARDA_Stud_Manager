#ifndef JSONKEYS_H
#define JSONKEYS_H

#include <QStringView>
#include <QStringList>

namespace JsonKeys {

inline constexpr QStringView ID = u"ID";
inline constexpr QStringView FIO = u"ФИО";
inline constexpr QStringView Group = u"Группа";
inline constexpr QStringView LessonName = u"Название Урока";
inline constexpr QStringView StudentGrades = u"Оценки Студента";
inline constexpr QStringView TestBook = u"Зачетная книжка";
inline constexpr QStringView Auto = u"Автомат";
inline constexpr QStringView ProjectName = u"Название Проекта";
inline constexpr QStringView Grade = u"Оценка";
inline constexpr QStringView Theme = u"Тема";
inline constexpr QStringView Curator = u"Куратор/Руководитель";
inline constexpr QStringView Date = u"Дата Сдачи";
inline constexpr QStringView StageWork = u"Этап Работы";
inline constexpr QStringView OtherData = u"Доп. Данные";

} // namespace JsonKeys

namespace Stages {

inline const QStringList StageList = {
    QStringLiteral("Выбрана тема"),
    QStringLiteral("В работе"),
    QStringLiteral("Сдано"),
    QStringLiteral("Защищено")
};

inline const QStringList StageListDiplom = {
    QStringLiteral("Тема предложена"),
    QStringLiteral("Тема утверждена"),
    QStringLiteral("В работе"),
    QStringLiteral("На проверке"),
    QStringLiteral("На доработке"),
    QStringLiteral("Готово к защите"),
    QStringLiteral("Защищено"),
    QStringLiteral("Отклонено")
};

} // namespace Stages


#endif // JSONKEYS_H
