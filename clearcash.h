#ifndef CLEARCASH_H
#define CLEARCASH_H
#include<QString>
#include<QList>

//на доработке
class ClearCash
{
private:
  inline static QStringList files = {"ValidatorLog.txt","AddStudentLog.txt","LoaderLog.txt",
                                    "LogCreateFS.txt","MoveFiles.log","FileManager.log"};
public:
    ClearCash();

public:
    static void clearCashFiles();
};

#endif // CLEARCASH_H
