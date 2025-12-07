#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <QObject>
#include<QTableWidgetItem>
class TableManager : public QObject
{
    Q_OBJECT
public:
    explicit TableManager(QTableWidget* table,QObject *parent = nullptr);

signals:

public slots:
    void processCellData(QTableWidgetItem* item);

    bool deleteDataTable();
private:
    QTableWidget* table_;
};

#endif // TABLEMANAGER_H
