#include "schedulebuilderform.h"
#include "ui_schedulebuilderform.h"
#include<QInputDialog>
#include"QFile"
#include"FileChooicer.h"
#include"LogicOperation.h"
#include<QTextStream>
#include"add_lesson_schedule_dialog.h"
#include"confrimdialog.h"
ScheduleBuilderForm::ScheduleBuilderForm(Add_Lesson_Schedule_Dialog *ALSD, QWidget *parent)
    : QWidget(parent)
    , MainMenu(ALSD)
    , scheudle(std::make_unique<DataSchedule>())
    , scheudleDataService(std::make_unique<ScheduleDataService>())
    , parseScheudle(std::make_unique<ScheduleJsonParser>())
    , ui(new Ui::ScheduleBuilderForm)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    // Или для более точного контроля:
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_DeleteOnClose);

    BuildDataComboBox();
    connect(ui->btnSave,&QPushButton::clicked,this,&ScheduleBuilderForm::SaveScheudle);
    connect(ui->btnRemove,&QPushButton::clicked,this,[this](){
        int row = QInputDialog::getInt(this,"Введите ключ расписания","Ввод");
        DeleteItemList(row);

    });

    connect(ui->btnCreateSheudle,&QPushButton::clicked,this,&ScheduleBuilderForm::BuildScheudle);

    connect(ui->btnQuit,&QPushButton::clicked,this,[this]()
    {
        ConfrimDialog* dialog = new ConfrimDialog(this);
        if(dialog->exec() == QDialog::Accepted)
        {
            this->backMenu();
        }
        else
        {
            return;
        }

    });



}

ScheduleBuilderForm::~ScheduleBuilderForm()
{
    delete ui;
}

void ScheduleBuilderForm::BuildScheudle()
{
    FileManager m;
    QFile file(m.saveFile());

    LogicOperation::ValidFile(file,ModeValidator::DeleteWrite);

    QJsonDocument doc(mainArr);
    file.write(doc.toJson());
    file.close();
}

void ScheduleBuilderForm::SaveScheudle()
{

    QFrame* frame = new QFrame(this);
    frame->setFrameStyle(QFrame::Box | QFrame::Raised);
    frame->setLineWidth(2);

    QVBoxLayout *mainLayout = new QVBoxLayout(frame);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    if (!ui->comboBoxTeacher->currentText().isEmpty()) {
        QLabel *labelTeacher = new QLabel("👨‍🏫 Преподаватель: " + ui->comboBoxTeacher->currentText(), frame);
        labelTeacher->setStyleSheet("font-size: 14px; font-weight: bold; color: #2c3e50;");
        mainLayout->addWidget(labelTeacher);
    }

    if (!ui->comboBoxCabinet->currentText().isEmpty()) {
        QLabel *labelCabinet = new QLabel("🏫 Кабинет: " + ui->comboBoxCabinet->currentText(), frame);
        labelCabinet->setStyleSheet("font-size: 14px; color: #27ae60;");
        mainLayout->addWidget(labelCabinet);
    }

    if (!ui->comboBoxLessonName->currentText().isEmpty()) {
        QLabel *labelLessonName = new QLabel("📚 Название: " + ui->comboBoxLessonName->currentText(), frame);
        labelLessonName->setStyleSheet("font-size: 14px; color: #2980b9;");
        mainLayout->addWidget(labelLessonName);
    }

    if (!ui->comboBoxTypeLesson->currentText().isEmpty()) {
        QLabel *labelTypeLesson = new QLabel("📝 Тип: " + ui->comboBoxTypeLesson->currentText(), frame);
        labelTypeLesson->setStyleSheet("font-size: 14px; color: #8e44ad;");
        mainLayout->addWidget(labelTypeLesson);
    }

    if (!ui->comboBoxLessonTime->currentText().isEmpty()) {
        QLabel *labelLessonTime = new QLabel("⏰ Время: " + ui->comboBoxLessonTime->currentText(), frame);
        labelLessonTime->setStyleSheet("font-size: 14px; color: #e74c3c;");
        mainLayout->addWidget(labelLessonTime);
    }

    if (ui->dateEditPair->date() > QDate::currentDate()) {
        QLabel *labelLessonTime = new QLabel("📅 Дата: " + ui->dateEditPair->date().toString("dd.MM.yyyy"), frame);
        labelLessonTime->setStyleSheet("font-size: 14px; color: #e74c3c;");
        mainLayout->addWidget(labelLessonTime);
    }

    QLabel * labelRow = new QLabel("🔐 Уникальный ключ расписания: " + QString::number(ui->listWidget->count()), frame);
    labelRow->setStyleSheet("font-size: 14px; color: #e74c3c;");
    mainLayout->addWidget(labelRow);

    QFrame *separator = new QFrame(frame);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    separator->setStyleSheet("background-color: #bdc3c7;");
    mainLayout->addWidget(separator);

    frame->setLayout(mainLayout);

    frame->setMinimumSize(300, 200);

    frame->setStyleSheet(
        "QFrame {"
        "  background-color: #ecf0f1;"
        "  border: 2px solid #3498db;"
        "  border-radius: 10px;"
        "}"
        );

    QListWidgetItem* item = new QListWidgetItem();

    item->setSizeHint(frame->sizeHint());

    ui->listWidget->addItem(item);

    ui->listWidget->setItemWidget(item, frame);



    SetLessonName(ui->comboBoxLessonName->currentText());

    QRegularExpression regex(R"(^(\d+)\s+(\d{1,2}:\d{2})\s*-\s*(\d{1,2}:\d{2})$)");
    QRegularExpressionMatch match = regex.match(ui->comboBoxLessonTime->currentText());

    if (match.hasMatch()) {
        int pair = match.captured(1).toInt();
        QTime time1 = QTime::fromString(match.captured(2), "HH:mm");
        QTime time2 = QTime::fromString(match.captured(3), "HH:mm");
        QPair<QTime,QTime> times = qMakePair(time1, time2);
        SetLessonTime(pair,times);
    }
    SetCabinets(ui->comboBoxCabinet->currentText());

    QTextStream stream(&ui->comboBoxTeacher->currentText());

    QString firstName, middleName, LastName;

    stream >> firstName >> middleName >> LastName;

    SetTeachers({firstName,middleName,LastName});
    SetDatePair(ui->dateEditPair->date());


    mainArr.append(parseScheudle->parseScheudleToJson(scheudle.get()));

}

void ScheduleBuilderForm::DeleteItemList(const int item_ROW)
{
    // QListWidgetItem* item =  ui->listWidget->item(item_ROW);
    // if(item != nullptr){
    //     ui->listWidget->removeItemWidget(item);
    //     delete item;

    // }
    delete ui->listWidget->takeItem(item_ROW);
}

void ScheduleBuilderForm::backMenu()
{
    this->close();
    MainMenu->show();
}

void ScheduleBuilderForm::BuildDataComboBox()
{
    ui->comboBoxCabinet->addItems({scheudleDataService->GetCabinetsJson().values()});
    ui->comboBoxLessonName->addItems({scheudleDataService->GetLessonNameJson().values()});

    ui->comboBoxTypeLesson->addItems({Lesson::lessonTypes});


    for(const auto& [pair,times] : scheudleDataService->GetLessonTimeJson().toStdMap())
    {
        QPair<QTime,QTime> t = std::move(times);
        ui->comboBoxLessonTime->addItem(QString::number(pair) + " " +t.first.toString("HH:mm") +" - " + t.second.toString("HH:mm"));
    }

    for(const auto& teacher : scheudleDataService->GetTeacherNameJson())
    {
        ui->comboBoxTeacher->addItem(teacher.firstName + " " + teacher.middleName + " " + teacher.lastName);

    }


}
