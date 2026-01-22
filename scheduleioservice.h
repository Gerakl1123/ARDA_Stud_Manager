#ifndef SCHEDULEIOSERVICE_H
#define SCHEDULEIOSERVICE_H

#include <QObject>
#include<QJsonArray>
#include<QJsonObject>
#include"FileChooicer.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include<QTextDocument>

class ScheduleIOService : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleIOService(QObject *parent = nullptr);

signals:

   // bool loadFromJson(const QString& filename);
   // bool loadFromXml(const QString& filename);


   // bool exportToExcel(const QJsonObject &obj) const;
   // bool exportToXML(const QJsonObject &obj) const;

public:
    bool exportToPDF(const QJsonArray &arr);
};

#endif // SCHEDULEIOSERVICE_H
