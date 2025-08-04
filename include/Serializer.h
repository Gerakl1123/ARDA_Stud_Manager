#ifndef SERIALIZER_H
#define SERIALIZER_H
#include<QWidget>


enum class ModeSerelization
{
    Attestat,
    MaxScore,
    ManagerStudent
};

class SerializerData
{
public:

    void DataSerelization(QWidget* w,ModeSerelization mode);

};

#endif // SERIALIZER_H
