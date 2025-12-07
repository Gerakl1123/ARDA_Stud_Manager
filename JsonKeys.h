#ifndef JSONKEYS_H
#define JSONKEYS_H

#include <QStringView>
#include <QStringList>

namespace JsonKeys {

inline static constexpr QStringView ID = u"ID";
inline static constexpr QStringView FIO = u"ФИО";
inline static constexpr QStringView Group = u"Группа";
inline static constexpr QStringView LessonName = u"Название Урока";
inline static constexpr QStringView StudentGrades = u"Оценки Студента";
inline static constexpr QStringView TestBook = u"Зачетная книжка";
inline static constexpr QStringView Auto = u"Автомат";
inline static constexpr QStringView ProjectName = u"Название Проекта";
inline static constexpr QStringView Grade = u"Оценка";
inline static constexpr QStringView Theme = u"Тема";
inline static constexpr QStringView Curator = u"Куратор/Руководитель";
inline static constexpr QStringView Date = u"Дата Сдачи";
inline static constexpr QStringView StageWork = u"Этап Работы";
inline static constexpr QStringView OtherData = u"Доп. Данные";
inline static constexpr QStringView MarksStudent = u"Марки Студента";
inline const QStringList headerLessons =
    {
    "ID",
    "ФИО",
    "Группа",
    "Название Урока",
    "Оценки Студента",
    "Марки Студента"
    };
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
namespace SerelizationData {
inline constexpr static auto ORG_NAME = "ARDA";
}

namespace DataKeys {
inline QStringList headers() {
    return {
        QStringLiteral("Имя"),
        QStringLiteral("Фамилия"),
        QStringLiteral("Отчество"),
        QStringLiteral("Пол"),
        QStringLiteral("Гражданство"),
        QStringLiteral("Место рождения"),
        QStringLiteral("Адрес проживания"),
        QStringLiteral("Серия паспорта"),
        QStringLiteral("Номер паспорта"),
        QStringLiteral("Кем выдан"),
        QStringLiteral("Код подразделения"),
        QStringLiteral("Дата выдачи"),
        QStringLiteral("День рождения")
    };
}

enum Columns {
    FirstName = 0,
    LastName,
    MiddleName,
    Gender,
    Citizenship,
    BirthPlace,
    Address,
    PassportSeries,
    PassportNumber,
    IssuedBy,
    DepartmentCode,
    IssueDate,
    BirthDate
};

}

namespace Passport {
inline const QStringList gender = {
    QStringLiteral("Мужской"),
    QStringLiteral("Женский")
};

inline static constexpr QStringView Address = u"Адресс проживания";
inline static constexpr QStringView Citizenship = u"Гражданство";
inline static constexpr QStringView IssueDate = u"Дата выдачи";
inline static constexpr QStringView BirthDate = u"День рождения";
inline static constexpr QStringView FirstName = u"Имя";
inline static constexpr QStringView IssuedBy = u"Кем выдан";
inline static constexpr QStringView DepartmentCode = u"Код подразделения";
inline static constexpr QStringView BirthPlace = u"Место рождения";
inline static constexpr QStringView PassportNumber = u"Номер пасспорта";
inline static constexpr QStringView MiddleName = u"Фамилия";
inline static constexpr QStringView LastName = u"Отчество";
inline static constexpr QStringView Gender = u"Пол";
inline static constexpr QStringView PassportSeries = u"Серия пасспорта";

inline const QStringList citizenship = {
    QStringLiteral("Австралия"),
    QStringLiteral("Австрия"),
    QStringLiteral("Азербайджан"),
    QStringLiteral("Албания"),
    QStringLiteral("Алжир"),
    QStringLiteral("Ангола"),
    QStringLiteral("Андорра"),
    QStringLiteral("Антигуа и Барбуда"),
    QStringLiteral("Аргентина"),
    QStringLiteral("Армения"),
    QStringLiteral("Афганистан"),
    QStringLiteral("Багамы"),
    QStringLiteral("Бангладеш"),
    QStringLiteral("Барбадос"),
    QStringLiteral("Бахрейн"),
    QStringLiteral("Беларусь"),
    QStringLiteral("Белиз"),
    QStringLiteral("Бельгия"),
    QStringLiteral("Бенин"),
    QStringLiteral("Бермуды"),
    QStringLiteral("Бутан"),
    QStringLiteral("Боливия"),
    QStringLiteral("Босния и Герцеговина"),
    QStringLiteral("Ботсвана"),
    QStringLiteral("Бразилия"),
    QStringLiteral("Бруней"),
    QStringLiteral("Буркина-Фасо"),
    QStringLiteral("Бурунди"),
    QStringLiteral("Вануату"),
    QStringLiteral("Ватикан"),
    QStringLiteral("Великобритания"),
    QStringLiteral("Венгрия"),
    QStringLiteral("Венесуэла"),
    QStringLiteral("Восточный Тимор"),
    QStringLiteral("Вьетнам"),
    QStringLiteral("Габон"),
    QStringLiteral("Гаити"),
    QStringLiteral("Гайана"),
    QStringLiteral("Гамбия"),
    QStringLiteral("Гана"),
    QStringLiteral("Гватемала"),
    QStringLiteral("Гвинея"),
    QStringLiteral("Гвинея-Бисау"),
    QStringLiteral("Германия"),
    QStringLiteral("Гондурас"),
    QStringLiteral("Гренада"),
    QStringLiteral("Греция"),
    QStringLiteral("Грузия"),
    QStringLiteral("Дания"),
    QStringLiteral("Джибути"),
    QStringLiteral("Доминика"),
    QStringLiteral("Доминиканская Республика"),
    QStringLiteral("Египет"),
    QStringLiteral("Замбия"),
    QStringLiteral("Зимбабве"),
    QStringLiteral("Израиль"),
    QStringLiteral("Индия"),
    QStringLiteral("Индонезия"),
    QStringLiteral("Иордания"),
    QStringLiteral("Ирак"),
    QStringLiteral("Иран"),
    QStringLiteral("Ирландия"),
    QStringLiteral("Исландия"),
    QStringLiteral("Испания"),
    QStringLiteral("Италия"),
    QStringLiteral("Йемен"),
    QStringLiteral("Кабо-Верде"),
    QStringLiteral("Казахстан"),
    QStringLiteral("Камбоджа"),
    QStringLiteral("Камерун"),
    QStringLiteral("Канада"),
    QStringLiteral("Катар"),
    QStringLiteral("Кения"),
    QStringLiteral("Кипр"),
    QStringLiteral("Киргизия"),
    QStringLiteral("Кирибати"),
    QStringLiteral("Китай"),
    QStringLiteral("Колумбия"),
    QStringLiteral("Коморы"),
    QStringLiteral("Конго"),
    QStringLiteral("КНДР"),
    QStringLiteral("Южная Корея"),
    QStringLiteral("Коста-Рика"),
    QStringLiteral("Кот-д'Ивуар"),
    QStringLiteral("Куба"),
    QStringLiteral("Кувейт"),
    QStringLiteral("Лаос"),
    QStringLiteral("Латвия"),
    QStringLiteral("Лесото"),
    QStringLiteral("Либерия"),
    QStringLiteral("Ливан"),
    QStringLiteral("Ливия"),
    QStringLiteral("Литва"),
    QStringLiteral("Лихтенштейн"),
    QStringLiteral("Люксембург"),
    QStringLiteral("Мадагаскар"),
    QStringLiteral("Малави"),
    QStringLiteral("Малайзия"),
    QStringLiteral("Мали"),
    QStringLiteral("Мальта"),
    QStringLiteral("Мальдивы"),
    QStringLiteral("Марокко"),
    QStringLiteral("Маршалловы Острова"),
    QStringLiteral("Мексика"),
    QStringLiteral("Мозамбик"),
    QStringLiteral("Молдова"),
    QStringLiteral("Монако"),
    QStringLiteral("Монголия"),
    QStringLiteral("Мьянма"),
    QStringLiteral("Намибия"),
    QStringLiteral("Науру"),
    QStringLiteral("Непал"),
    QStringLiteral("Нигер"),
    QStringLiteral("Нигерия"),
    QStringLiteral("Нидерланды"),
    QStringLiteral("Никарагуа"),
    QStringLiteral("Новая Зеландия"),
    QStringLiteral("Норвегия"),
    QStringLiteral("Объединённые Арабские Эмираты"),
    QStringLiteral("Оман"),
    QStringLiteral("Пакистан"),
    QStringLiteral("Палау"),
    QStringLiteral("Панама"),
    QStringLiteral("Папуа — Новая Гвинея"),
    QStringLiteral("Парагвай"),
    QStringLiteral("Перу"),
    QStringLiteral("Польша"),
    QStringLiteral("Португалия"),
    QStringLiteral("Руанда"),
    QStringLiteral("Румыния"),
    QStringLiteral("Россия"),
    QStringLiteral("Сальвадор"),
    QStringLiteral("Самоа"),
    QStringLiteral("Сан-Марино"),
    QStringLiteral("Сан-Томе и Принсипи"),
    QStringLiteral("Саудовская Аравия"),
    QStringLiteral("Северная Македония"),
    QStringLiteral("Сейшельские Острова"),
    QStringLiteral("Сенегал"),
    QStringLiteral("Сент-Винсент и Гренадины"),
    QStringLiteral("Сент-Китс и Невис"),
    QStringLiteral("Сент-Люсия"),
    QStringLiteral("Сербия"),
    QStringLiteral("Сингапур"),
    QStringLiteral("Сирия"),
    QStringLiteral("Словакия"),
    QStringLiteral("Словения"),
    QStringLiteral("Соломоновы Острова"),
    QStringLiteral("Сомали"),
    QStringLiteral("Южный Судан"),
    QStringLiteral("Судан"),
    QStringLiteral("Суринам"),
    QStringLiteral("Сьерра-Леоне"),
    QStringLiteral("Таджикистан"),
    QStringLiteral("Таиланд"),
    QStringLiteral("Танзания"),
    QStringLiteral("Того"),
    QStringLiteral("Тонга"),
    QStringLiteral("Тринидад и Тобаго"),
    QStringLiteral("Тувалу"),
    QStringLiteral("Тунис"),
    QStringLiteral("Туркмения"),
    QStringLiteral("Турция"),
    QStringLiteral("Уганда"),
    QStringLiteral("Узбекистан"),
    QStringLiteral("Украина"),
    QStringLiteral("Уругвай"),
    QStringLiteral("Фиджи"),
    QStringLiteral("Филиппины"),
    QStringLiteral("Финляндия"),
    QStringLiteral("Франция"),
    QStringLiteral("Хорватия"),
    QStringLiteral("Центральноафриканская Республика"),
    QStringLiteral("Чад"),
    QStringLiteral("Черногория"),
    QStringLiteral("Чехия"),
    QStringLiteral("Чили"),
    QStringLiteral("Швейцария"),
    QStringLiteral("Швеция"),
    QStringLiteral("Шри-Ланка"),
    QStringLiteral("Эквадор"),
    QStringLiteral("Экваториальная Гвинея"),
    QStringLiteral("Эритрея"),
    QStringLiteral("Эсватини"),
    QStringLiteral("Эстония"),
    QStringLiteral("Эфиопия"),
    QStringLiteral("Южно-Африканская Республика"),
    QStringLiteral("Соединённые Штаты Америки"),
    QStringLiteral("Южный Судан"),
    QStringLiteral("Ямайка"),
    QStringLiteral("Япония"),
    QStringLiteral("Палестина"),
    QStringLiteral("Косово"),
    QStringLiteral("Тайвань"),
    QStringLiteral("Западная Сахара"),
    QStringLiteral("Северный Кипр"),
    QStringLiteral("Абхазия"),
    QStringLiteral("Южная Осетия"),
    QStringLiteral("Палестинская территория"),
    QStringLiteral("Сомалиленд"),
    QStringLiteral("Транснистрия"),
    QStringLiteral("Республика Арцах бывш. Карабах")
};
}

namespace extension {
inline const QStringList fileExtension=
    {
    QStringLiteral(""), // Без расшире6ния
    QStringLiteral(".txt"),
    QStringLiteral(".json"),
    QStringLiteral(".pdf")
    };
}


namespace ManagerFSKeys {
inline const QStringList sorts =
    {
        QStringLiteral("По дате"),
        QStringLiteral("По имени"),
        QStringLiteral("По Размеру")
    };
}

namespace Planner {

inline static QString Works = "./Works.json";
}

enum class DatabaseTypes {
    LESSON = 0,
    ACADEMIC,
    PROJECT,
    COURSE,
    DIPLOMA
};



#endif // JSONKEYS_H
