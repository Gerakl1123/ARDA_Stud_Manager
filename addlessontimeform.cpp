#include "addlessontimeform.h"
#include "ui_addlessontimeform.h"
#include"FileManagerCore/managerfs.h"
#include<QBoxLayout>
#include<QPair>
#include<QTime>


void AddLessonTimeForm::contextMenuEvent(QContextMenuEvent *event)
{
    QTreeWidgetItem* item = ui->treeWidget->itemAt(event->pos());
    createContextMenu(item,event->pos());

}

void AddLessonTimeForm::onDeleteItem()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if (!item) {
        return;
    }
    QString itemText = item->text(0);
    if (itemText.contains("пара",Qt::CaseInsensitive)) {


        int t = item->text(0).at(0).digitValue();

        if(scheudle->lessonsTime.contains(t)){
            scheudle->lessonsTime.remove(t);

            delete item;
            ui->comboBox->insertItem(t-1,"Пара " + QString::number(t));
            //ui->comboBox->
            return;
        }

    }
    return;

}

void AddLessonTimeForm::createContextMenu(QTreeWidgetItem *item, const QPoint &pos)
{
    QMenu menu(this);

    QAction *deleteAction = menu.addAction("Удалить");

    if (!item) {
        deleteAction->setEnabled(false);
    }

    QAction *selectedAction = menu.exec(QCursor::pos());

    if (!selectedAction) return;

    if (selectedAction == deleteAction) {
        onDeleteItem();
    }
}

AddLessonTimeForm::AddLessonTimeForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddLessonTimeForm)
{
    ui->setupUi(this);
    {
    QGridLayout* pbxLayout = new QGridLayout(this);

    QList<QWidget*> allWidgets = this->findChildren<QWidget*>();
    QList<QWidget*> topLevelWidgets;
    ui->treeWidget->setHeaderHidden(true);
    ui->treeWidget->setIndentation(20);
    ui->treeWidget->setAnimated(true);
    ui->treeWidget->setRootIsDecorated(true);


    for(const auto& w : allWidgets)
    {
        if (w == this) continue;

        if (w->parent() != this) {
            continue;
        }

        topLevelWidgets.append(w);
    }

    std::sort(topLevelWidgets.begin(),topLevelWidgets.end(),[](QWidget* a,QWidget* b){
        return a->pos().y() < b->pos().y() || (a->pos().y() == b->pos().y() && a->pos().x() < b->pos().x());
    });

    for(const auto& w : topLevelWidgets)
    {
        pbxLayout->addWidget(w);
    }

    this->setLayout(pbxLayout);
    }
    ManagerWorker w;
    w.CreateDir(".","Расписание");
    parseJson = std::make_unique<ScheduleJsonParser>();
    scheudle = std::make_unique<DataSchedule>();

     QStringList pairs= {
        "Пара 1",
        "Пара 2",
        "Пара 3",
        "Пара 4",
        "Пара 5",
        "Пара 6",
        "Пара 7",
        "Пара 8",
    };

    ui->comboBox->setPlaceholderText("Пары");
    ui->comboBox->addItems(pairs);

    connect(ui->btnSave,&QPushButton::clicked,this,&AddLessonTimeForm::setDataLessonTime);
    connect(ui->btnGo,&QPushButton::clicked,[this](){

        QString fileName = "Расписание/lesson_time.json";

       bool success =  parseJson->setDataLessonTime(fileName,scheudle->lessonsTime);

        success ? QMessageBox::information(this,"Добавление","Пары успешно отправлены")
               : QMessageBox::warning(this,"Добавление","Пары не удалось отправить");
    });

    connect(ui->btnDefault,&QPushButton::clicked,this,&AddLessonTimeForm::setDefaultDataLessonTime);

}

AddLessonTimeForm::~AddLessonTimeForm()
{
    delete ui;
}

void AddLessonTimeForm::setDefaultDataLessonTime()
{
    scheudle->intanceTimeLessonDefault();
    ui->comboBox->clear();

    for(const auto& [pair,times] : scheudle->lessonsTime.asKeyValueRange())
    {
        QTime startTime = times.first;
        QTime endTime = times.second;


        ui->treeWidget->setColumnCount(1);
        ui->treeWidget->setHeaderHidden(true);

        QTreeWidgetItem* mainItem = nullptr;

        if (ui->treeWidget->topLevelItemCount() == 0) {
            mainItem = new QTreeWidgetItem(ui->treeWidget);
            mainItem->setText(0, "ПАРЫ");
            ui->treeWidget->addTopLevelItem(mainItem);
        } else {
            mainItem = ui->treeWidget->topLevelItem(0);
            mainItem->setIcon(0,QIcon{":/icons/vetv.png"});
        }


        QTreeWidgetItem* pairItem = new QTreeWidgetItem(mainItem);
        pairItem->setText(0, QString::number(pair) + " пара");

        pairItem->setIcon(0,QIcon{":/icons/vetv.png"});

        QTreeWidgetItem* startTimeItem = new QTreeWidgetItem(pairItem);
        startTimeItem->setText(0,"Начало: " + startTime.toString("HH:mm"));

        QTreeWidgetItem* endTimeItem = new QTreeWidgetItem(pairItem);
        endTimeItem->setText(0,"Конец: " + endTime.toString("HH:mm"));

        startTimeItem->setHidden(false);
        endTimeItem->setHidden(false);

        pairItem->setFlags(pairItem->flags() | Qt::ItemIsAutoTristate | Qt::ItemIsUserCheckable);

         pairItem->setExpanded(true);
         mainItem->setExpanded(true);

    }

    QMessageBox::information(this, "Добавление", "Успешно");


}


void AddLessonTimeForm::setDataLessonTime()
{
    if(ui->comboBox->currentText().isEmpty()) return;
    QString pairStr = ui->comboBox->currentText();

    int index = ui->comboBox->currentIndex();
    ui->comboBox->removeItem(index);

    pairStr.remove("Пара ");
    int pair= pairStr.toInt();

    QTime startTime = ui->timeEdit_Start->time();
    QTime endTime = ui->timeEdit_End->time();

    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderHidden(true);

    QTreeWidgetItem* mainItem = nullptr;

    if (ui->treeWidget->topLevelItemCount() == 0) {
        mainItem = new QTreeWidgetItem(ui->treeWidget);
        mainItem->setText(0, "ПАРЫ");
        ui->treeWidget->addTopLevelItem(mainItem);
    } else {
        mainItem = ui->treeWidget->topLevelItem(0);
        mainItem->setIcon(0,QIcon{":/icons/vetv.png"});
    }


    QTreeWidgetItem* pairItem = new QTreeWidgetItem(mainItem);
    pairItem->setText(0, pairStr + " пара");

    pairItem->setIcon(0,QIcon{":/icons/vetv.png"});

    QTreeWidgetItem* startTimeItem = new QTreeWidgetItem(pairItem);
    startTimeItem->setText(0,"Начало: " + startTime.toString("HH:mm"));

    QTreeWidgetItem* endTimeItem = new QTreeWidgetItem(pairItem);
    endTimeItem->setText(0,"Конец: " + endTime.toString("HH:mm"));

    startTimeItem->setHidden(false);
    endTimeItem->setHidden(false);

    pairItem->setFlags(pairItem->flags() | Qt::ItemIsAutoTristate | Qt::ItemIsUserCheckable);

    pairItem->setExpanded(true);
    mainItem->setExpanded(true);

    scheudle->lessonsTime[pair] = qMakePair(startTime, endTime);

    ui->timeEdit_Start->setTime(QTime(0, 0));
    ui->timeEdit_End->setTime(QTime(0, 0));



    QMessageBox::information(this, "Добавление", "Успешно");
}
