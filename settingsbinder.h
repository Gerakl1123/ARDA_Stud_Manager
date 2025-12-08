#ifndef SETTINGSBINDER_H
#define SETTINGSBINDER_H

#include <QObject>
#include<QLineEdit>
#include<QSettings>
#include<QTableWidget>
#include"LogicOperation.h"

class SettingsBinder : public QObject
{
    Q_OBJECT
public:
    explicit SettingsBinder(QObject *parent);

public:
    void ConnectionsContest(QLineEdit* line, const QString& org, const QString& app, const QString& key);
    void ConnectionsGradesMenu(QTableWidget* table,const QString& org,const QString& app);
    void ConnectionsCourseWork(QTableWidget* t,const QString& org,const QString& app);
    void ConnectionsDiploma(QTableWidget* t,const QString& org,const QString& app);

    void ConnectionsExtra(QWidget* thisWidget,const QString& org, const QString& app);
    void ConnectionsPassport(QWidget* thisWidget,const QString& org, const QString& app);

private:
    std::unique_ptr<LogicOperation> logicOperation;
};

#endif // SETTINGSBINDER_H
