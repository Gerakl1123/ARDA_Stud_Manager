#ifndef DYNAMICCREATEFORMEDITORDATAJSON_H
#define DYNAMICCREATEFORMEDITORDATAJSON_H

#include<QTableView>
#include<QStandardItemModel>
#include"dataeditor.h"
#include<QVBoxLayout>
#include"builderform.h"
#include"LogicOperation.h"
#include<QThread>
#include<QList>
#include<QHash>
class DynamicCreateFormEditorDataJSON : public QWidget
{
    Q_OBJECT
public:
    explicit DynamicCreateFormEditorDataJSON(DataEditor* form,QWidget *parent = nullptr);

    bool setDataTable(const QList<QHash<QString,QString>>&);
    bool SaveEditedData();
    ~DynamicCreateFormEditorDataJSON();
private:
    QThread* workThread;
    LogicOperation* logicWorker;

    DataEditor* formEditor;
    QTableView* tableView;
    QStandardItemModel* model;
    QString filePath;

    QPushButton* back;
    QPushButton* Save;
    QVBoxLayout* layaout;
    BuilderForm* Builder;

private:
    void initUI();
};

#endif // DYNAMICCREATEFORMEDITORDATAJSON_H
