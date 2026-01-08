#ifndef ADDLESSONTIMEFORM_H
#define ADDLESSONTIMEFORM_H

#include <QWidget>
#include"schedulejsonparser.h"
#include"dataschedule.h"
#include <QContextMenuEvent>
#include <QMenu>
#include<QTreeWidgetItem>
namespace Ui {
class AddLessonTimeForm;
}

class AddLessonTimeForm : public QWidget
{
    Q_OBJECT

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
private slots:
    void onDeleteItem();

private:
    void createContextMenu(QTreeWidgetItem *item, const QPoint &pos);
public:
    explicit AddLessonTimeForm(QWidget *parent = nullptr);
    ~AddLessonTimeForm();

private:
    Ui::AddLessonTimeForm *ui;
    std::unique_ptr<ScheduleJsonParser> parseJson;
    std::unique_ptr<DataSchedule> scheudle;
    void setDefaultDataLessonTime();
    void setDataLessonTime();
};



#endif // ADDLESSONTIMEFORM_H
