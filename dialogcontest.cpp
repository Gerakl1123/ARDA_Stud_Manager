#include "dialogcontest.h"
#include "ui_dialogcontest.h"

DialogContest::DialogContest(DialogMode mode, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogContest)
    , currentMode(mode)
{
    ui->setupUi(this);
    ui->lineEditContest->setStyleSheet("QLineEdit { border: 2px solid #ccc; border-radius: 6px; padding: 6px 10px; font-size: 14px; }");
    ui->label->setStyleSheet("QLabel { color: #666; font-size: 14px; font-weight: bold; }");

    setWindowTitle("ПодМеню");

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DialogContest::handleAccepted);

    setupInterface();
}

DialogContest::~DialogContest()
{
    delete ui;
}

void DialogContest::setupInterface()
{
    switch (currentMode) {
    case ModeCurrent:
        ui->lineEditContest->show();
        ui->label->show();
        ui->labelFile->hide();
        ui->labelFakyltet->hide();
        ui->labelFile->hide();
        ui->labelOnBudget->hide();
        ui->labelReadFile->hide();
        ui->lineEditBall->hide();
        ui->lineEditFakyltet->hide();
        ui->lineEditFileSave->hide();
        ui->lineEditFile->hide();
        break;
    case ModeAttestat:
        ui->lineEditContest->hide();
        ui->label->hide();
        break;
    }
}

qint64 DialogContest::OnBudget()
{
    CurretContest contest;
    QString QFakyltet = ui->lineEditFakyltet->text();
    QString ballSTR = ui->lineEditBall->text();
    QString file = ui->lineEditFile->text();
    QString savefile = ui->lineEditFileSave->text();

    bool ok = true;
    double ballValue = ballSTR.toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Некорректное значение балла");
        return -1;
    }

    std::string fileSTR = file.toStdString();
    std::string saveFileSTR = savefile.toStdString();

    qint64 count = contest.ContestBudget(ballValue, fileSTR, saveFileSTR, QFakyltet);

    if(count)
        QMessageBox::information(this, "Конкурс Аттестатов",
                             QString("Данные добавлены в файл.\nПоступило: %1 студентов").arg(count));
    else
        QMessageBox::information(this, "Конкурс Аттестатов",
                                 "Нет студентов соответствующих этим критериям");

    return count;
}

QString DialogContest::getInputText()
{
    return ui->lineEditContest->text();
}

void DialogContest::ok_Button_Click()
{
    accept();
}

void DialogContest::handleAccepted()
{
    if(OnBudget() > 0 )
        this->accept();
    else
        QMessageBox::information(this, "Неизвестная ошибка",
                             "-__-");
}

