#include "primarydatascheudlemanagerform.h"
#include "ui_primarydatascheudlemanagerform.h"
#include<QPropertyAnimation>
#include<QParallelAnimationGroup>

PrimaryDataScheudleManagerForm::PrimaryDataScheudleManagerForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PrimaryDataScheudleManagerForm)
{
    ui->setupUi(this);

    setupForm();

    setWindowTitle("Управление учебным процессом");
    this->setLayout(ui->gridLayout);

    connect(ui->btnTeacher, &QPushButton::clicked, this, &PrimaryDataScheudleManagerForm::onTeachersClicked);
    connect(ui->btnCab, &QPushButton::clicked, this, &PrimaryDataScheudleManagerForm::onCabinetsClicked);
    connect(ui->btnLesson, &QPushButton::clicked, this, &PrimaryDataScheudleManagerForm::onLessonTimeClicked);
    connect(ui->btnLessonName,&QPushButton::clicked,this,&PrimaryDataScheudleManagerForm::onLessonNameClicked);
    onLessonTimeClicked();
}

PrimaryDataScheudleManagerForm::~PrimaryDataScheudleManagerForm()
{
    delete ui;
}

void PrimaryDataScheudleManagerForm::onTeachersClicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    highlightButton(ui->btnTeacher);
}

void PrimaryDataScheudleManagerForm::onCabinetsClicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    highlightButton(ui->btnCab);
}

void PrimaryDataScheudleManagerForm::onLessonTimeClicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    highlightButton(ui->btnLesson);
}

void PrimaryDataScheudleManagerForm::onLessonNameClicked()
{

    ui->stackedWidget->setCurrentIndex(3);

    highlightButton(ui->btnLessonName);
}


void PrimaryDataScheudleManagerForm::setupForm()
{
    lessonPage = new AddLessonTimeForm(this);
    cabinetsPage = new AddCabinetsDialog(this);
    teachesPage = new AddNameTeachersForm(this);
    lessonName = new AddLessonNameForm(this);

    while (ui->stackedWidget->count() > 0) {
        QWidget* widget = ui->stackedWidget->widget(0);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }

    ui->stackedWidget->addWidget(lessonPage);
    ui->stackedWidget->addWidget(cabinetsPage);
    ui->stackedWidget->addWidget(teachesPage);
    ui->stackedWidget->addWidget(lessonName);


}


void PrimaryDataScheudleManagerForm::highlightButton(QPushButton *activeBtn)
{
    QList<QPushButton*> navButtons = {
        ui->btnLesson,
        ui->btnCab,
        ui->btnTeacher
    };

    for (QPushButton *btn : navButtons) {
        if (btn == activeBtn) {
            btn->setStyleSheet(
                "QPushButton {"
                "    background-color: #0078d7;"
                "    color: white;"
                "    border: 2px solid #005a9e;"
                "    font-weight: bold;"
                "    padding: 8px;"
                "}"
                );
        } else {
            btn->setStyleSheet(
                "QPushButton {"
                "    background-color: #f0f0f0;"
                "    color: #333333;"
                "    border: 1px solid #cccccc;"
                "    padding: 8px;"
                "}"
                "QPushButton:hover {"
                "    background-color: #e0e0e0;"
                "}"
                );
        }
    }
}

