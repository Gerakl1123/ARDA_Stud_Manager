#ifndef LOGICOPERATION_H
#define LOGICOPERATION_H
#include"Logger.h"
#include"Validator.h"
#include"Loader.h"
#include<QTextEdit>
#include<optional>
#include<QTableWidgetItem>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include"ModeValidator.h"
#include<QDir>
#include<QtSql/QSqlQuery>
#include"JsonKeys.h"

class TelegramNotifier;
struct Task;
class SerializerData;

class LogicOperation
{
public:
    bool handleAddStudent(const QString& file, const QString& data,QLineEdit* LineEditClear,QWidget* parent);
    QString handlePriviewFile(const QString& file,QTextEdit* display,QWidget* parent);
    bool handleSortStudent(const QString& file,const QString& saveFile,QWidget* parent);
    void handleDeleteStudent(const QString& file,const QString& name, const QString& score, QWidget* parent);
    void handleFindStudent(const QString& file, const QString& name, const QString& score,QWidget* parent);

    std::optional<double> handleAutoTestStudent(QTableWidgetItem* checkItem,QList<int>& averageScore);

    double converterTOnumberInString(const QString& number);

    void FillSettingsTable(QSettings& settings,QTableWidget* t);
    void FillTableWidget(QSettings& settings,QTableWidget* t,int row,int column);
    void FillTableWidgetCourse(QWidget *p, QSettings& settings, QTableWidget* t, QString& app);
    void FillTableWidgetDiploma(QWidget* p, QSettings& settings, QTableWidget* t, QString& app);

    void FillTableAdminInfo(QWidget* p,QTableWidget* t);

    static QJsonArray rewriteFile(QFile& file);
    static QJsonArray rewriteFileManagGrades(QTableWidget* t,QFile& file);

    static QFileInfoList recursiveTravelDirs(const QString& path);

     void validNums(QString &values);


     static bool createTableDBfromTYPE(const DatabaseTypes type, const QSqlDatabase& db);
    static QString nameFileDb(DatabaseTypes type);


     bool sendNotificationWorksTG(TelegramNotifier* tg, const QSet<qint64>& chats,const QVector<Task>& currentTask);

    static void ValidFile(QFile& file,const ModeValidator& mode);

     bool DeleteKeyFromRegEdit(const QString& value,const QString& App);


    //  void LoadTableHeaders(QSettings &settings, QTableWidget *t);
    // void SaveTableHeaders(QSettings &settings, QTableWidget *t);

};


#endif // LOGICOPERATION_H
