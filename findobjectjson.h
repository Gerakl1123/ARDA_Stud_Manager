#ifndef FINDOBJECTJSON_H
#define FINDOBJECTJSON_H

#include <QDialog>
#include"FileChooicer.h"
namespace Ui {
class FindObjectJson;
}

class FindObjectJson : public QDialog
{
    Q_OBJECT

public:
    explicit FindObjectJson(QWidget *parent = nullptr);
    ~FindObjectJson();
signals:
    QString getID(const QString& ID);
    QString getNameFile(const QString& file);
    QString  getNameFileExtra(const QString& file);
    void FillList();
private:
    Ui::FindObjectJson *ui;
    FileManager* fileManager;
};

#endif // FINDOBJECTJSON_H
