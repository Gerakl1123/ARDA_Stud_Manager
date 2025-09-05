#ifndef CLEARCASH_H
#define CLEARCASH_H
#include<QString>
#include<QList>

//на доработке
class ClearCash
{
private:
  inline static QList<QString> files = {"C:/Users/Gera/Desktop/Setup/resource/ValidatorLog.txt",
        "C:/Users/Gera/Desktop/Setup/resource/AddStudentLog.txt",
        "C:/Users/Gera/Desktop/Setup/resource/LoaderLog.txt"};

public:
    ClearCash();

public:
    static void clearCashFiles();
};

#endif // CLEARCASH_H
