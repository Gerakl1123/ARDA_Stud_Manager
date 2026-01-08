#include "addcabinetsdialog.h"
#include "ui_addcabinetsdialog.h"
#include<QMessageBox>
#include <QShortcut>

AddCabinetsDialog::AddCabinetsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddCabinetsDialog)
    , schedule(std::make_unique<DataSchedule>())
    , parseJson(std::make_unique<ScheduleJsonParser>())
{
        ui->setupUi(this);

     this->setLayout(ui->gridLayout);

        ManagerWorker w;
        w.CreateDir(".","Расписание");

        QShortcut* shortcut = new QShortcut(QKeySequence("Enter"),this);
        connect(shortcut, &QShortcut::activated, this, [this](){
            auto success = ui->lineEditCab->text().isEmpty();

            if(!success)
            {
                ui->listWidgetPriview->addItem("Кабинет:" + ui->lineEditCab->text());

            }
        });

    connect(ui->btnSave,&QPushButton::clicked,[this](){
        auto success = ui->lineEditCab->text().isEmpty();

        if(!success)
        {
            ui->listWidgetPriview->addItem("Кабинет:" + ui->lineEditCab->text());

        }

    });



    connect(ui->listWidgetPriview,&QListWidget::clicked,[this](const QModelIndex& index){
        int curr = index.row();

        QListWidgetItem* item = ui->listWidgetPriview->item(curr);

        if (item) {
            delete ui->listWidgetPriview->takeItem(curr);
        }

    });

    connect(ui->btnHelp,&QPushButton::clicked,[this](){
        QMessageBox::information(
            this,
            "Подсказка по меню",
            "📌 Как работать с меню:\n\n"
            "1️⃣ Введите данные кабинета и нажмите «Сохранить».\n"
            "   Данные появятся в списке.\n\n"
            "2️⃣ Если какие-то данные введены неверно —\n"
            "   просто нажмите на этот кабинет в списке,\n"
            "   он будет удалён.\n\n"
            "3️⃣ Если есть дубликаты — не переживайте.\n"
            "   При отправке ARDA автоматически их отсеет.\n\n"
            "4️⃣ Когда всё проверено и добавлено,\n"
            "   нажмите кнопку «Отправить»."
        );

    });

    connect(ui->btnGo,&QPushButton::clicked,this,&AddCabinetsDialog::SendCabinetsDataToJson);

}

AddCabinetsDialog::~AddCabinetsDialog()
{
    delete ui;
}

bool AddCabinetsDialog::SendCabinetsDataToJson()
{
    if(ui->listWidgetPriview->count() == 0){
        QMessageBox::warning(this,"Ошибка отправки","А кабинеты где?");
        return false;

    }

    for(int i = 0; i<ui->listWidgetPriview->count(); i++)
    {
        QString str = std::move(ui->listWidgetPriview->item(i)->text().remove("Кабинет:"));
        schedule->cabinets.insert(str);
    }
    QString file = "Расписание/cabinets.json";

    bool success = parseJson->setDataCabinets(file,schedule->cabinets);
    if(success)
    {
        QMessageBox::warning(this,"Ошибка отправки","что то вставить данные не получислось\n\n Проверь папку Расписание по пути программы или перезапусти прогу");

        return success;
    }

    return success;

}
