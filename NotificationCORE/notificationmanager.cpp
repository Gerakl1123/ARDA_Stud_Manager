#include "notificationmanager.h"
#include "ui_notificationmanager.h"
#include "../Validator.h"
#include <QSystemTrayIcon>
#include "../JsonKeys.h"
#include "../LogicOperation.h"
#include <QList>
#include <QString>
#include <QTimer>
#include <QMessageBox>

NotificationManager::NotificationManager(AssignmentPlanner *planner, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NotificationManager),
    parser(std::make_unique<ParserJson>()),
    planner_(planner)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    instance();
    setupConnections();
}

NotificationManager::~NotificationManager()
{
    delete ui;
}

void NotificationManager::backMenu()
{
    this->close();
    planner_->show();
}

void NotificationManager::updateNotifications()
{
    QTimer::singleShot(500, this, [this]() {
        tasksInfo.clear();
        chatIDs.clear();
        SetChtsInfo();
        SetTaskInfo();

        QSettings& settings = NotificationManager::instanceSettings();
        int count = settings.value("Count").toInt();

        if (count > 0) {
            for (int i = 1; i <= count; i++) {
                chatIDs.insert(settings.value(QString("ID%1").arg(i)).toLongLong());
            }
        }

        emit getIDTelegramUser(chatIDs);
        qDebug() << "АЙДИ ОТПРАВЛЕНЫ ИЗ МЕНЕДЖЕРА" << chatIDs.size();
        emit getTasks(tasksInfo);
    });
}

int NotificationManager::getInt(Notification&& notif)
{
    return static_cast<int>(notif);
}

void NotificationManager::SetChtsInfo()
{

    QSettings& settings = NotificationManager::instanceSettings();

    int countAcc = 1;
    int count = settings.value("Count").toInt(nullptr);

    if(count > 0){
        while(countAcc <= count)
        {
            chatIDs.insert( settings.value(QString("ID%1").arg(countAcc)).toLongLong() );
            countAcc++;
        }
        qDebug() << "АЙДИ В МЕНЕДЖЕРЕ" << chatIDs.size();
    }

    QStringList list;
    QString string;

    for (qint64 value : chatIDs) {
        QString string = QString::number(value);
        list.append(string);
    }

    ui->comboBox->addItems(list);
}

void NotificationManager::SetTaskInfo()
{
    QFile file(Planner::Works);
    try
    {
        Validator::isFileValid(file, ModeValidator::ReadFile);
    }
    catch(const std::logic_error& e)
    {
        QMessageBox::warning(this, "Error", e.what());
        return;
    }

    QByteArray bArr = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(bArr);
    QJsonArray arr(doc.array());

    for(const auto &c : arr)
    {
        if(!c.isObject()) continue;
        QJsonObject obj = c.toObject();
        tasksInfo.emplaceBack(parser->UploadWork(obj));
    }
}

void NotificationManager::instance()
{
    QSettings& settings = NotificationManager::instanceSettings();

    ui->checkBox->setCheckState(static_cast<Qt::CheckState>(settings.value("Notification").toInt()));
    Frequency_of_Messages_System = settings.value("SpinBoxSystem").toInt();
    Frequency_of_Messages_TG = settings.value("SpinBoxTG").toInt();
    ui->spinBoxSystemNotification->setValue(Frequency_of_Messages_System);
    ui->spinBoxTelegramNotification->setValue(Frequency_of_Messages_TG);

    int count = settings.value("Count").toInt();

    if (count > 0) {
        for (int i = 1; i <= count; i++) {
            chatIDs.insert(settings.value(QString("ID%1").arg(i)).toLongLong());
        }
        qDebug() << "АЙДИ В МЕНЕДЖЕРЕ" << chatIDs.size();
    }

    QStringList list;
    for (qint64 value : chatIDs) {
        list.append(QString::number(value));
    }

    ui->comboBox->addItems(list);
}

void NotificationManager::setupConnections()
{
    connect(ui->btnSaveChatID, &QPushButton::clicked, this, [this]() {
        bool ok = false;
        qint64 chatID = ui->lineEditTgChatID->text().toLongLong(&ok);

        if(ok) {
            chatIDs.insert(chatID);
            QMessageBox::information(this, "Сохраненое", "Вы можете подключить еще аккаунты для получения уведомлений");
            ui->lineEditTgChatID->setText("");

            QSettings& settings = NotificationManager::instanceSettings();
            int countID = 0;

            for (qint64 value : chatIDs) {
                ++countID;
                settings.setValue(QString("ID%1").arg(countID), value);
            }
            settings.setValue("Count", countID);
            settings.sync();

            QStringList list;
            for (qint64 value : chatIDs) {
                list.append(QString::number(value));
            }
            ui->comboBox->clear();
            ui->comboBox->addItems(list);
        }
        else {
            QMessageBox::warning(this, "Не кореектный ID", "Не обманывай программу CHAT ID перепроверь!");
        }
    });

    connect(ui->checkBox, &QCheckBox::checkStateChanged, this, [this](int state) {
        QSettings& settings = NotificationManager::instanceSettings();
        settings.setValue("Notification", state);
        emit CurrentState(state);
    });

    connect(ui->spinBoxSystemNotification, &QSpinBox::valueChanged, this, [this](int val) {
        QSettings& settings = NotificationManager::instanceSettings();
        settings.setValue("SpinBoxSystem", val);
        Frequency_of_Messages_System = val;
    });

    connect(ui->spinBoxTelegramNotification, &QSpinBox::valueChanged, this, [this](int val) {
        QSettings& settings = NotificationManager::instanceSettings();
        settings.setValue("SpinBoxTG", val);
        Frequency_of_Messages_TG = val;
    });

    connect(ui->btnDeleteChatID, &QPushButton::clicked, this, [this]() {
        bool result = logic->DeleteKeyFromRegEdit(ui->comboBox->currentText(), "Todo");
        if(result) {
            ui->comboBox->removeItem(ui->comboBox->currentIndex());
        }
    });

    connect(ui->btnQuit, &QPushButton::clicked, this, &NotificationManager::backMenu);
}

void NotificationManager::NotificationStart(Notification notific, std::optional<std::reference_wrapper<const Task>> data)
{
    if(tasksInfo.empty()) {
        QSystemTrayIcon icon;
        icon.setIcon(QIcon(":icons/not.png"));
        icon.setToolTip("ARDA Manager");
        icon.show();
        icon.showMessage("Задач нету",
                         "Вы выполнили все задачи поздравляем вас и я тоже :)",
                         QSystemTrayIcon::Information,
                         getInt(Notification::NoTask));
        return;
    }

    if(ui->checkBox->isChecked() && data.has_value()) {
        const Task& task = data->get();
        QSystemTrayIcon* trayIcon = new QSystemTrayIcon;

        trayIcon->setIcon(QIcon(":/icons/Delete.png"));
        trayIcon->setToolTip("ARDA Manager-ToDo");
        trayIcon->show();

        trayIcon->showMessage(
            "📋 У вас есть активная задача",
            "Задача: " + task.nameT + "\n"
            "📅 Срок: " + task.dateT.toString("dd.MM.yyyy") + "\n"
            "⏰ Время: " + task.timeT.toString("hh:mm") + "\n"
            "⚡ Приоритет: " + task.priorityT,
            QSystemTrayIcon::Information,
            getInt(std::move(notific))
            );

        // connect(trayIcon, &QSystemTrayIcon::messageClicked, this, [this]() {
        //     if (!priview_) {
        //         priview_ = new PriviewWorks(planner_);
        //     }
        //     priview_->exec();
        // });

        QTimer::singleShot(getInt(std::move(notific)) + 1000, trayIcon, &QSystemTrayIcon::deleteLater);
    }
}

void NotificationManager::runSystemNotification()
{
    for(const auto& c : tasksInfo) {
        if(c.priorityT == "Легкий") {
            NotificationStart(Notification::Easy, std::cref(c));
        }
        else if(c.priorityT == "Нормальный") {
            NotificationStart(Notification::Normal, std::cref(c));
        }
        else if(c.priorityT == "Высший") {
            NotificationStart(Notification::High, std::cref(c));
        }
        else if(c.priorityT == "Экстримальный") {
            NotificationStart(Notification::Extreme, std::cref(c));
        }
        else {
            NotificationStart(Notification::NoTask);
        }
    }
}

int NotificationManager::get_Frequency_of_Messages_System()
{
    return Frequency_of_Messages_System;
}

int NotificationManager::get_Frequency_of_Messages_TG()
{
    return Frequency_of_Messages_TG;
}

int NotificationManager::getCurrentState() const
{
    return static_cast<int>(ui->checkBox->checkState());
}
