#ifndef UPDATECHECKER_H
#define UPDATECHECKER_H
#include <QObject>
#include <QString>
#include <QUrl>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include"parserjsonnetwork.h"
#include"CurrentVersionApplication.h"


class UpdateChecker : public QObject
{
    Q_OBJECT
public:
    explicit UpdateChecker(QObject* parent = nullptr);
    void checkUpdate();

    ~UpdateChecker();
signals:
    void updateAvailable(QString version);
    void noUpdate();
    void networkError(QString error);

private slots:
    void CheckData(QNetworkReply* rep);

private:
    QNetworkAccessManager* networkManager;
    QNetworkReply* reply;
    ParserJsonNetWork* parser;
    QString ReadyVersion;
};


#endif // UPDATECHECKER_H
