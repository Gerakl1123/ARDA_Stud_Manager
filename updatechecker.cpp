#include "updatechecker.h"
#include<QObject>
#include<QMessageBox>
#include"LogicOperation.h"
#include<QDesktopServices>

UpdateChecker::UpdateChecker(QObject *parent) :
    QObject(parent)

{
    networkManager = new QNetworkAccessManager(this);
    parser = new ParserJson;

    connect(networkManager,&QNetworkAccessManager::finished,this,&UpdateChecker::CheckData);

}
UpdateChecker::~UpdateChecker() {
    delete networkManager;
    delete parser;
}


void UpdateChecker::CheckData(QNetworkReply* rep)
{
    if (rep->error() == QNetworkReply::NoError)
    {
        QString json = rep->readAll();
        ReadyVersion = parser->ReadyDataVersion(json);

        LogicOperation lo;
        double ver = lo.converterTOnumberInString(ReadyVersion);
        double curr_ver = lo.converterTOnumberInString(Version::CURRENT_VERSION);

        if (ver > curr_ver)
            emit updateAvailable(ReadyVersion);
        else
            emit noUpdate();
    }
    else
    {
        emit networkError(rep->errorString());
    }

    rep->deleteLater();
}


void UpdateChecker::checkUpdate()
{
    QUrl url("https://gerakl1123.github.io/ARDA_web/update.json");
    QNetworkRequest request(url);
    reply = networkManager->get(request);

}
