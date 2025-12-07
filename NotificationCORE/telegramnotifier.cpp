#include "telegramnotifier.h"

#include<QTime>
#include<QTimer>
#include"../xorstr.h"
TelegramNotifier::TelegramNotifier(NotificationManager *notifM, QObject *parent)
    : QObject{parent}
    , notifM_(notifM)
{
    manager = new QNetworkAccessManager(this);

}


void TelegramNotifier::checkCommand()
{
    QUrl urlToken = QUrl::fromUserInput(
        QString("https://api.telegram.org/bot%1/getUpdates?offset=%2")
            .arg(xorstr("Пока тут не будет токен бота"))
            .arg(lastUpdateId + 1)
        );

    QNetworkRequest request(urlToken);
    QNetworkReply* reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray bArr = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(bArr);
            QJsonObject rootObj = doc.object();

            if (rootObj["ok"].toBool()) {
                QJsonArray arr = rootObj["result"].toArray();

                for(const auto& c : arr) {
                    if(!c.isObject()) continue;

                    QJsonObject updateObj = c.toObject();

                    qint64 updateId = updateObj["update_id"].toVariant().toLongLong();
                    lastUpdateId = updateId;

                    QJsonObject messageObj = updateObj["message"].toObject();
                    QJsonObject chatObj = messageObj["chat"].toObject();

                    qint64 currentChatID = chatObj["id"].toVariant().toLongLong();
                    QString chatId = chatObj["id"].toString();
                    QString command = messageObj["text"].toString();

                    if(command == "/myid")
                    {
                      //*logger<<"Введена команда \\myid" << currentChatID;
                        sendMessage(currentChatID, QString("Ваш CHAT_ID ПЕРЕЙДИТЕ В ОПОВЕЩЕНИЯ И ВСТАВЬТЕ ID: %1").arg(currentChatID));
                    }else if(command == "/remove")
                    {

                        sendMessage(currentChatID, QString("Ваш id удален с реестра"));
                        QSettings settings(SerelizationData::ORG_NAME,"Todo");

                        QStringList allKeys = settings.allKeys();

                        for(const auto& c : allKeys)
                        {
                            qint64 currentTargetValue = settings.value(c).toLongLong();

                            if(currentChatID == currentTargetValue)
                            {
                                settings.remove(c);
                                settings.sync();
                                break;
                            }

                        }
                    }
                    else
                    {
                        //*logger<< "Не известная команда: " + command;
                        sendMessage(currentChatID,"Неизвестная команда");
                    }
                }
            }
        }
        reply->deleteLater();
    });
}

void TelegramNotifier::sendMessage(quint64 chatID, const QString &msg)
{
    QUrl url(QString("https://api.telegram.org/bot%1/sendMessage").arg(xorstr("пока тут не будет токен бота")));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["chat_id"] = QString::number(chatID);
    obj["text"] = msg;

    QNetworkReply* reply = manager->post(request,QJsonDocument(obj).toJson());

    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() != QNetworkReply::NoError) {
           // *logger<< reply->errorString();
        }
        reply->deleteLater();
     //  *logger<< "Успешно ОТПРАВЛЕНО!";
    });

}

void TelegramNotifier::setCurrentTask(const QVector<Task> &tasks)
{
    current_task_user = tasks;
}
