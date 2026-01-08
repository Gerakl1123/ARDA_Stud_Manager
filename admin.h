#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include"IOCore/IODataHandler.h"
#include"findobjectjson.h"
#include"parserjson.h"
#include<QStringListModel>

class MainWindow;

namespace Ui {
class ADMIN;
}

class ADMIN : public QWidget
{
    Q_OBJECT

public:
    explicit ADMIN(MainWindow* main, QWidget *parent = nullptr);
    ~ADMIN();

private:
    Ui::ADMIN *ui;
    MainWindow* mainWindow;   // указател на главное окно
    QString ID_;
    QString FileName_;
    QString FileNameExtra_;

    std::unique_ptr<ImportSaveData> isd;
    QJsonObject objectPass;
    QJsonObject objectExtra;

    FindObjectJson* findObject;
    std::unique_ptr<ParserJson> parser;
    QStringListModel* modelPassport;
    QStringListModel* modelExtra;

private slots:
    void openFindObject();

    void SaveNumber(const QString& ID);
    void SaveFileName(const QString& fileName);
    void SaveFileNamextra(const QString& FileName);

};

#endif // ADMIN_H
