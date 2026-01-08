#include "priviewworks.h"
#include "ui_priviewworks.h"
#include<QFile>
#include"../Validator.h"
#include<QJsonArray>
#include<QPushButton>
#include<QListWidgetItem>
#include<QJsonValue>
#include<QJsonObject>
#include"../JsonKeys.h"
PriviewWorks::PriviewWorks(AssignmentPlanner *planner, QWidget *parent)
    : QDialog(parent)
    , planner_(planner)
    , parser(std::make_unique<ParserJson>())
    , ui(new Ui::PriviewWorks)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    QObject::connect(ui->btnLeave,&QPushButton::clicked,this,[this](){
        planner_->show();
        this->close();
    });

    w = new AddWork(this,planner_,nullptr);


    priviewWorks();
    BuildWorks();
}

PriviewWorks::~PriviewWorks()
{
    delete ui;
}

void PriviewWorks::openWorks(int local)
{
   // QPushButton* button = qobject_cast<QPushButton*>(sender());

    QFile file(Planner::Works);
    try
    {
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }
    catch(const std::invalid_argument& e)
    {

    }


    QByteArray bArr(file.readAll());
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(bArr,&error);

    QJsonArray arr(doc.array());

    int counter = 0;
    for(const auto& c : arr)
    {
        if(counter == local)
        {
            if(c.isObject())
            {
                QJsonObject obj = c.toObject();
                qDebug() << "2. Найден объек испускаю сигнал";

                qDebug() << "Объект:" << obj;
                //PriviewWorks* p;
                emit Priview(obj);
                qDebug() << "3. Сигнал испущен";

                this->close();
                w->show();
                qDebug() << "4. Окно скрыто";
                return;
            }
        }
        ++counter;
    }


}


void PriviewWorks::priviewWorks()
{


    QFile file(Planner::Works);
    try
    {
        Validator::isFileValid(file,ModeValidator::ReadFile);
    }
    catch(const std::invalid_argument& e)
    {
        QMessageBox::warning(this,"Ошибка открытие файла","Ошибка открытия файла возмодно он удален проверьте вашу папку на наличее Works.json");
        return;
    }
    QByteArray bArr(file.readAll());
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(bArr,&error);
    QJsonArray arr(doc.array());
    CurrArr = arr;
    if(error.error == QJsonParseError::NoError)
    {
        works = static_cast<int>(arr.size());
    }

    file.close();

}

void PriviewWorks::BuildWorks()
{

    infoList = parser->getInfoWorks(CurrArr);
    qDebug() <<QString::number(infoList.size());
    int local = 0;

    while(local < works)
    {

        auto& taskTuple = infoList.at(local);

        QString taskName = std::get<0>(taskTuple);
        QDate taskDate = std::get<1>(taskTuple);
        QTime taskTime = std::get<2>(taskTuple);
        qDebug() << taskDate.isValid();

        QPushButton* button = new QPushButton(
            "🎯 Задача " + QString::number(local + 1) + "\n"
                                                        "📝 " + taskName + "\n"
                             "🗓 " + taskDate.toString("dd.MM.yyyy") + "   ⏰ " + taskTime.toString("HH:mm"),
            this
        );

        QPushButton* buttonDeleter = new QPushButton(QIcon(":/icons/Delete.png"),"",this);
        buttonDeleter->setIconSize(QSize(32, 32));
        buttonDeleter->setToolTip("Если сделал удаляй не засоряй\n Works.json");
        buttonDeleter->setProperty("index",local);

        connect(button, &QPushButton::clicked, this, [this, local]() {
            openWorks(local);
        });

        connect(buttonDeleter, &QPushButton::clicked, this, [this, buttonDeleter]() {
            int curr = buttonDeleter->property("index").toInt();
            parser->DeleteObjectInArrayWorks(curr);

            QListWidgetItem* item = ui->listWidgetPriview->item(curr);
            if (item) {
                delete ui->listWidgetPriview->takeItem(curr);
            }
            QListWidgetItem* itemDel = ui->listWidgetDeleter->item(curr);
            if (itemDel) {
                delete ui->listWidgetDeleter->takeItem(curr);
            }

        });



        QListWidgetItem* item = new QListWidgetItem();
        QListWidgetItem* itemDel = new QListWidgetItem();

        item->setSizeHint(button->sizeHint());
        itemDel->setSizeHint(button->sizeHint());

        ui->listWidgetPriview->addItem(item);
        ui->listWidgetPriview->setItemWidget(item, button);

        ui->listWidgetDeleter->addItem(itemDel);
        ui->listWidgetDeleter->setItemWidget(itemDel, buttonDeleter);


        ++local;
    }
}
