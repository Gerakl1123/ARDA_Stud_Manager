#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QSystemTrayIcon>
#include <QJsonObject>
#include <QSettings>
#include <QRandomGenerator>
#include"addwork.h"
#include"../parserjson.h"
#include"priviewworks.h"
#include"assignmentplanner.h"
#include<optional>
#include<functional>
#include"../LogicOperation.h"

namespace Ui {
class NotificationManager;
}

enum class Notification
{
    Easy = 10000,
    Normal = 15000,
    High = 20000,
    Extreme = 30000,
    NoTask = 10000

};
class NotificationManager : public QWidget
{
    Q_OBJECT

public:
    explicit NotificationManager(AssignmentPlanner* planner, QWidget *parent = nullptr);
    ~NotificationManager();
    int get_Frequency_of_Messages_System();
    int get_Frequency_of_Messages_TG();
    void setcurrentDate(const QDate& date, const QTime& t);
    static QSettings& instanceSettings() {
        static QSettings settings(SerelizationData::ORG_NAME, "Todo");
        return settings;
    }

public slots:
    void runSystemNotification();
    void updateNotifications();
    int getCurrentState() const;
    void backMenu();
    int getCurrentStateTG() const;

    void compareNotifictionDate();

signals:
    void getTasks(const QVector<Task>& tasks);
    void CurrentState(int state);
    void getIDTelegramUser(const QSet<qint64>& id);
    void stateCheckBox(int state);
private:
    // System Notification
    QVector<Task> tasksInfo;

    // Telegram
    QSet<qint64> chatIDs;

    Ui::NotificationManager *ui;

    AssignmentPlanner* planner_;
    PriviewWorks* priview_;
    std::unique_ptr<ParserJson> parser;
    static inline auto logic = std::make_shared<LogicOperation>();

    int Frequency_of_Messages_System = 30;
    int Frequency_of_Messages_TG = 30;
    inline static std::pair<QDate, QTime> currentDataTime =
        std::make_pair(QDate::currentDate(), QTime::currentTime());

private:
    void NotificationStart(const Notification notific, std::optional<std::reference_wrapper<const Task>> data = std::nullopt);
    void SetTaskInfo();
    void SetChtsInfo();
    void instance();
    void setupConnections();
    int getInt(Notification &&notif);
};

#endif // NOTIFICATIONMANAGER_H
