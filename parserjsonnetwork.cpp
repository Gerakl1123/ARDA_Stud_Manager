#include "parserjsonnetwork.h"
#include<QFile>
#include"Validator.h"
#include<QMessageBox>

ParserJsonNetWork::ParserJsonNetWork()
{

}

QString ParserJsonNetWork::ReadyDataVersion(const QString& jsonDataServer)
{

    QJsonDocument doc = QJsonDocument::fromJson(jsonDataServer.toUtf8());

    if (!doc.isObject()) {
        QMessageBox::warning(nullptr, "Error", "Не коректный json");
        return "";
    }

    QJsonObject obj = doc.object();
    QString ver = obj["version"].toString();

    return ver;
}
