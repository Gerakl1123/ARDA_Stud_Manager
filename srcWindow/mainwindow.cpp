#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../include/Student.h"
#include "../academicrecordwindow.h"
#include "../updatechecker.h"

#include <QMenuBar>
#include <QMessageBox>
#include <QDebug>
#include <QStyleFactory>
#include <QThread>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupMenu();
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete AdminPanel;
    delete windowContest;
    delete windowLesson;
    delete windowStudent;
}

void MainWindow::setupMenu()
{
    auto menuBar = new QMenuBar(this);
    auto aboutMenu = new QMenu("Справка", menuBar);

    auto actionAbout      = new QAction("О программе", aboutMenu);
    auto actionUpdate     = new QAction("Проверка обновлений", aboutMenu);
    auto actionClearCache = new QAction("Очистить кеш", aboutMenu);

    aboutMenu->addActions({ actionAbout, actionUpdate, actionClearCache });
    menuBar->addMenu(aboutMenu);
    setMenuBar(menuBar);

    connect(actionAbout, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(actionUpdate, &QAction::triggered, this, &MainWindow::checkForUpdates);
    connect(actionClearCache, &QAction::triggered, this, &ClearCash::clearCashFiles);
}

void MainWindow::setupConnections()
{
    connect(ui->pushButtonAppStyle, &QPushButton::clicked, this, &MainWindow::ToggleStyleApp);
    connect(ui->ButtonStudent,      &QPushButton::clicked, this, &MainWindow::openManagerStud);
    connect(ui->ButtonContest,      &QPushButton::clicked, this, &MainWindow::openContestWindow);
    connect(ui->ButtoLessons,       &QPushButton::clicked, this, &MainWindow::openLessons);
    connect(ui->ButtonADMINPANEL,   &QPushButton::clicked, this, &MainWindow::openADMINPANEL);
}


void MainWindow::checkForUpdates()
{
    auto updater = new UpdateChecker;
    auto updateThread = new QThread(this);

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
                             "Создатель: Герман Ниязян\nКонтакты: @GermanNiyazyan");
}


void MainWindow::openLessons()
{
    windowLesson = new academicrecordwindow(this);
    qDebug() << "Окно Lessons создано";
    close();
    windowLesson->show();
}

void MainWindow::openManagerStud()
{
    windowStudent = new StudentDataService(this);
    qDebug() << "Окно Student создано";
    close();
    windowStudent->show();
}

void MainWindow::openContestWindow()
{
    windowContest = new contestwindow(this);
    qDebug() << "Окно Contest создано";
    close();
    windowContest->show();
}

void MainWindow::openADMINPANEL()
{
    AdminPanel = new ADMIN(this);
    qDebug() << "Окно ADMIN создано";
    close();
    AdminPanel->show();
}


void MainWindow::ToggleStyleApp()
{
    qApp->setStyle(QStyleFactory::create("Fusion"));

    if (!StyleChoice) {
        QPalette darkPalette;
        darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(42, 42, 42));
        darkPalette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Highlight, QColor(142, 45, 197).lighter());
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);
        qApp->setPalette(darkPalette);
        StyleChoice = true;
    } else {
        QPalette lightPalette;
        lightPalette.setColor(QPalette::Window, QColor(255, 255, 255));
        lightPalette.setColor(QPalette::WindowText, Qt::black);
        lightPalette.setColor(QPalette::Base, QColor(245, 245, 245));
        lightPalette.setColor(QPalette::AlternateBase, QColor(255, 255, 255));
        lightPalette.setColor(QPalette::ToolTipBase, Qt::black);
        lightPalette.setColor(QPalette::ToolTipText, Qt::white);
        lightPalette.setColor(QPalette::Text, Qt::black);
        lightPalette.setColor(QPalette::Button, QColor(240, 240, 240));
        lightPalette.setColor(QPalette::ButtonText, Qt::black);
        lightPalette.setColor(QPalette::BrightText, Qt::red);
        lightPalette.setColor(QPalette::Highlight, QColor(76, 163, 224));
        lightPalette.setColor(QPalette::HighlightedText, Qt::white);
        qApp->setPalette(lightPalette);
        StyleChoice = false;
    }
}
