#ifndef IODATABASEHANDLER_H
#define IODATABASEHANDLER_H
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlError>
#include<QTableWidget>
#include"../JsonKeys.h"
#include"../Logger.h"

class IODataBaseHandler
{
public:
    IODataBaseHandler();
    ~IODataBaseHandler();
private:
    static inline std::shared_ptr<Log> logger = Log::create("dbLOG.log");
    void InsertDataInDB(const QString &name,QStringList& keys,QStringList &values);
     bool createConnectionsDB(const DatabaseTypes type, const QString &other_data_db = "");

    QSqlDatabase db;
public:
    void loadDataLesson(QTableWidget* table);
    void loadDataAcademic(QTableWidget* table);

    void saveDataLesson(QTableWidget* table, const QString &other);
    void saveDataAcademic(QTableWidget* table,const QString &other);
};

#endif // IODATABASEHANDLER_H
