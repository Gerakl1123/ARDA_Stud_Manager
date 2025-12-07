#ifndef TELEGRAMNOTIFIER_H
#define TELEGRAMNOTIFIER_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include<QUrlQuery>

#include <QJsonDocument>
#include <QJsonObject>
#include<QJsonValue>
#include <QJsonArray>

#include <QSettings>

#include"../Logger.h"

#include"notificationmanager.h"
class TelegramNotifier : public QObject
{
    Q_OBJECT
public:
    explicit TelegramNotifier(NotificationManager* notifM, QObject *parent = nullptr);
    QNetworkAccessManager* manager;
    int lastUpdateId = 0;

public slots:
    //void getChatID();
    void checkCommand();
    void sendMessage(quint64 chatID,const QString& msg);

    void setCurrentTask(const QVector<Task>& tasks);

private:
    static inline auto logger = Log::create("TelegramNotificationConnections.log");
    QVector<Task> current_task_user;
    NotificationManager* notifM_;
};

#endif // TELEGRAMNOTIFIER_H
