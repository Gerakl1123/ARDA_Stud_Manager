#ifndef DATASCHEDULE_H
#define DATASCHEDULE_H

#include <QObject>
#include <QList>
#include<QString>
#include<QMap>
#include<QTime>
#include <QHash>


static constexpr size_t MAX_LESSON = 8;

namespace Lesson {

enum class Type_Lesson {
    Lecture,
    Practice,
    Lab_Work,
    Seminar,
    Consultation,
    Exam,
    Credit_Test,
    Course_Project,
    Diploma_Project,
    Elective,
    Self_Study,
    Colloquium
};

const QList<QString> lessonTypes = {
    "Лекция",
    "Практика",
    "Лабораторная",
    "Семинар",
    "Консультация",
    "Экзамен",
    "Зачет",
    "Курсовая работа",
    "Дипломная работа",
    "Факультатив",
    "Самостоятельная работа",
    "Коллоквиум"
};

}

struct Teacher {
    QString lastName;
    QString firstName;
    QString middleName;
    Teacher() = default;

    Teacher(const QString& name,const QString& MiddleName,const QString& LastName)
        : firstName(name),middleName(MiddleName),lastName(LastName)
    {

    }
    bool operator==(const Teacher& other) const {
        return lastName == other.lastName
               && firstName == other.firstName
               && middleName == other.middleName;
    }

    QString getFullName() const
    {
        return firstName + " " + middleName + " " + lastName;
    }
};
inline size_t qHash(const Teacher &t, size_t seed = 0)
{
    return qHash(t.lastName, seed)
    ^ qHash(t.firstName, seed << 1)
        ^ qHash(t.middleName, seed << 2);
}


struct DataSchedule
{
    typedef QMap<int, QPair<QTime,QTime>> DataMapLessonTime;
    DataSchedule() = default;

    DataMapLessonTime intanceTimeLessonDefault();
public:

    QSet<QString> cabinets;
    QSet<Teacher> Teachers;
    QSet<QString> LessonsName;
    DataMapLessonTime lessonsTime;
    QSet<QDate> datePair;


public:

    QString currentLessonName;
    Teacher currentTeacher;
    QString currentCabinet;
    QDate currentDate;
    int currentPair;
    QTime currentStartTime;
    QTime currentEndTime;
};

#endif // DATASCHEDULE_H
