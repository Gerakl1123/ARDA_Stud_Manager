#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "StudentManagerCore/Student.h"
#include "LessonsCore/academicrecordwindow.h"
#include "updatechecker.h"
#include"ardaeditorform.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QDebug>
#include <QStyleFactory>
#include <QThread>
#include <QTimer>
#include<QDesktopServices>
#include"CurrentVersionApplication.h"
#include"NotificationCORE/notificationmanager.h"
#include"NotificationCORE/telegramnotifier.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labelVersion->setText("Версия ПО: " + Version::CURRENT_VERSION);



       // AssignmentPlanner* planner = new AssignmentPlanner(this,nullptr);


    NotificationManager* manager = new NotificationManager(nullptr,nullptr);
    TelegramNotifier* tg = new TelegramNotifier(manager,nullptr);

    QTimer* updateNotific = new QTimer(this);

    connect(updateNotific,&QTimer::timeout,manager,&NotificationManager::updateNotifications);
    updateNotific->start(5000);

        connect(manager,&NotificationManager::getIDTelegramUser,this,&MainWindow::setChats);
        connect(manager,&NotificationManager::getTasks,this,&MainWindow::setTasks);
        connect(manager,&NotificationManager::getTasks,tg,&TelegramNotifier::setCurrentTask);


        QTimer* timer = new QTimer(manager);

         QObject::connect(manager, &NotificationManager::CurrentState, [timer, manager](int state){
             if(state == 2) {
                 QObject::connect(timer, &QTimer::timeout, manager, &NotificationManager::runSystemNotification);
                 timer->start((manager->get_Frequency_of_Messages_System() * 60 * 1000));

             } else if(state == 0){

                 QMessageBox::information(nullptr, "Уведомления",
                                          "Системные уведомления выключены для их включения передите\n"
                                          "Планировщик Задач-> Оповещения->Системные Уведомления-> и нажмити на чекбокс");
             }
         });


         //Праверка на включение системные уведомлений
         QTimer::singleShot(100, [manager]() {
             int currentState = manager->getCurrentState();
             qDebug() << "Состояние: " << currentState;
             emit manager->CurrentState(currentState);

         });

         // Проверка на ввод команд в боте
        QTimer* timerCheckCommand = new QTimer(this);
        connect(timerCheckCommand,&QTimer::timeout,tg,&TelegramNotifier::checkCommand);
        timerCheckCommand->start(1000);

        //Отправка сообщений в тг
        QTimer* timerSendNotificationTG = new QTimer(this);

         connect(timerSendNotificationTG,&QTimer::timeout,[tg,this](){
             LogicOperation l;
             l.sendNotificationWorksTG(tg,NotificationChatsIDTG,tasks);
        });

        timerSendNotificationTG->start((manager->get_Frequency_of_Messages_TG() * 60 * 1000));

    setupMenu();

    setupConnections();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setChats(const QSet<qint64> &chats)
{
    NotificationChatsIDTG = chats;
    qDebug() << "setChats вызван! Получено чатов:" << chats.size();
}

void MainWindow::setTasks(const QVector<Task> &task)
{
    tasks = task;
    qDebug() << "setTasks вызван! Получено задач:" << tasks.size();
}

void MainWindow::setupMenu()
{
    auto menuBar = new QMenuBar(this);
    auto aboutMenu = new QMenu("Справка", menuBar);
    auto aboutDoc = new QMenu("Документация/Обучение", menuBar);

    auto actionProjectDoc = new QAction("Документация по проекту",aboutDoc);
    auto actionEducationDoc = new QAction("Обучение по ПО",aboutDoc);


    auto actionAbout      = new QAction("О программе", aboutMenu);
    auto actionUpdate     = new QAction("Проверка обновлений", aboutMenu);
    auto actionClearCache = new QAction("Очистить кеш", aboutMenu);

    aboutMenu->addActions({ actionAbout, actionUpdate, actionClearCache });
    aboutDoc->addActions({actionProjectDoc,actionEducationDoc});
    menuBar->addMenu(aboutDoc);
    menuBar->addMenu(aboutMenu);
    setMenuBar(menuBar);

    connect(actionAbout, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(actionUpdate, &QAction::triggered, this, &MainWindow::checkForUpdates);
    connect(actionClearCache, &QAction::triggered, this, &ClearCash::clearCashFiles);
    connect(actionProjectDoc,&QAction::triggered,this,&MainWindow::openDoc);
}

void MainWindow::setupConnections()
{
    connect(ui->ButtonStudent,      &QPushButton::clicked, this, &MainWindow::openManagerStud);
    connect(ui->ButtonContest,      &QPushButton::clicked, this, &MainWindow::openContestWindow);
    connect(ui->ButtoLessons,       &QPushButton::clicked, this, &MainWindow::openLessons);
    connect(ui->ButtonADMINPANEL,   &QPushButton::clicked, this, &MainWindow::openADMINPANEL);
    connect(ui->ButtonFileManag,    &QPushButton::clicked, this, &MainWindow::openFileManger);
    connect(ui->btnTextEditor,      &QPushButton::clicked, this, &MainWindow::openTextEditor);
    connect(ui->btnToDo,            &QPushButton::clicked, this, &MainWindow::openAssigmentPlanner);

}


void MainWindow::checkForUpdates()
{
    auto updater = new UpdateChecker;
    auto updateThread = new QThread;

    updater->moveToThread(updateThread);

    connect(updateThread, &QThread::started, updater, &UpdateChecker::checkUpdate);

    connect(updater, &UpdateChecker::updateAvailable, this, &MainWindow::onUpdateAvailable);
    connect(updater, &UpdateChecker::noUpdate, this, &MainWindow::onNoUpdate);
    connect(updater, &UpdateChecker::networkError, this, &MainWindow::onNetworkError);

    connect(updater, &UpdateChecker::updateAvailable, updateThread, &QThread::quit);
    connect(updater, &UpdateChecker::noUpdate, updateThread, &QThread::quit);
    connect(updater, &UpdateChecker::networkError, updateThread, &QThread::quit);

    connect(updateThread, &QThread::finished, updater, &QObject::deleteLater);
    connect(updateThread, &QThread::finished, updateThread, &QObject::deleteLater);

    updateThread->start();
}


void MainWindow::onUpdateAvailable(const QString &ver)
{
    QMetaObject::invokeMethod(this, [this, ver]() {
        QMessageBox::information(this, "Обновление", "Доступно обновление: " + ver);
    }, Qt::QueuedConnection);
}

void MainWindow::onNoUpdate()
{
    QMetaObject::invokeMethod(this, [this]() {
        QMessageBox::information(this, "Обновление", "У вас установлена последняя версия");
    }, Qt::QueuedConnection);
}

void MainWindow::onNetworkError(const QString &err)
{
    QMetaObject::invokeMethod(this, [this, err]() {
        QMessageBox::information(this, "Обновление", err);
    }, Qt::QueuedConnection);
}


void MainWindow::showAboutDialog()
{
    QMessageBox::information(this, "О создателе",
                             "Создатель: Герман Ниязян\nКонтакты: @NiyazyanGerman");
}


void MainWindow::openLessons()
{
    academicrecordwindow* windowLesson = new academicrecordwindow(this);
    qDebug() << "Окно Lessons создано";
    windowLesson->setAttribute(Qt::WA_DeleteOnClose);
    hide();
    windowLesson->show();
}

void MainWindow::openManagerStud()
{
    StudentDataService* windowStudent = new StudentDataService(this);
    qDebug() << "Окно Student создано";
    hide();
    windowStudent->show();
}

void MainWindow::openContestWindow()
{
    contestwindow* windowContest = new contestwindow(this);
    qDebug() << "Окно Contest создано";
    windowContest->setAttribute(Qt::WA_DeleteOnClose);
    hide();
    windowContest->show();
}

void MainWindow::openADMINPANEL()
{
    ADMIN* AdminPanel = new ADMIN(this);
    qDebug() << "Окно ADMIN создано";
    AdminPanel->setAttribute(Qt::WA_DeleteOnClose);
    hide();
    AdminPanel->show();
}

void MainWindow::openFileManger()
{
    filemanagerdialog* fmd = new filemanagerdialog(this);
    qDebug() << "Окно FileManager создано";
    fmd->setAttribute(Qt::WA_DeleteOnClose);
    hide();
    fmd->show();
}

void MainWindow::openTextEditor()
{
    ArdaEditorForm* editor = new ArdaEditorForm(this);
    editor->setAttribute(Qt::WA_DeleteOnClose);
    hide();
    editor->show();
}

void MainWindow::openDoc()
{
    QDesktopServices::openUrl(QUrl("https://gerakl1123.github.io/ARDA_web/doc.html"));
}

void MainWindow::openAssigmentPlanner()
{
    AssignmentPlanner* planner= new AssignmentPlanner(this);
    planner->setAttribute(Qt::WA_DeleteOnClose);
    hide();
    planner->show();
}
