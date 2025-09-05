#ifndef SERIALIZER_H
#define SERIALIZER_H
#include<QWidget>
#include<QTableWidget>
#include<QTableWidgetItem>

enum class ModeSerelization
{
    Attestat,
    MaxScore,
    ManagerStudent,
    Lessons,
    Records,
    Projects,
    CourseWork
};

class SerializerData
{
public:

    void DataSerelization(QWidget* w,ModeSerelization mode);
    void DataSerelizationMenuStudentRecords(QTableWidget* t,QWidget* p,ModeSerelization);
    void DataSerelizationCourse(QTableWidget* t,QWidget* p);

};

#endif // SERIALIZER_H
