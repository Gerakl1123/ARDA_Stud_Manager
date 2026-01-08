#ifndef DATAEDITOR_H
#define DATAEDITOR_H

#include <QWidget>
#include<QMouseEvent>
#include"FileChooicer.h"
#include<QDragEnterEvent>
#include<QMutex>
class MainWindow;
class DynamicCreateFormEditorDataJSON;
namespace Ui {
class DataEditor;
}

class DataEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DataEditor(MainWindow* qMain,QWidget *parent = nullptr);
    ~DataEditor();
signals:
    void GetInfoData(const QList<QHash<QString,QString>>&);
    void getFileName(const QString& file);
public slots:
    void mousePressEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void getData();


private:
    void back();
    void addDragOverStyle();
    void removeDragOverStyle();
    bool m_dragOver = false;
    Ui::DataEditor *ui;
    std::unique_ptr<FileManager> fileChooicer;
    QString fileName;
    DynamicCreateFormEditorDataJSON* JSONFormCreator;
    MainWindow* main_;

};

#endif // DATAEDITOR_H
