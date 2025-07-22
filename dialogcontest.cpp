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

    SerelizationDeserelization();


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

        for(int i = 0; i< ui->gridLayout->count();++i)
        {
            QWidget* w = ui->gridLayout->itemAt(i)->widget();
            if(w)
            {
                w->hide();
            }
        }
        break;
    case ModeAttestat:

        for (int i = 0; i < ui->verticalLayout->count(); ++i) {

            QWidget *w = ui->verticalLayout->itemAt(i)->widget();

            if (w)
            {
               w->hide();
            }
        }


        break;
    }
}

qint64 DialogContest::OnBudget()
{
    CurrentContest contest;
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

QString DialogContest::onContest()
{
    QString contest = ui->lineEditContest->text();
    QString LogFile = ui->lineEditFileLogContest->text();
    QString fileSave = ui->lineEditFileSaveContest->text();
    QString inputFile = ui->lineEditFileInputContest->text();

    CurrentContest Maincontest(contest.toStdString(),LogFile.toStdString());

   QString winner = Maincontest.currentContest(fileSave.toStdString(),inputFile.toStdString());

    if(!winner.toStdString().empty())
    {
       QMessageBox::information(this,
                                "Конкурс " + contest,
                                QString("Данные добавлены в файл.\nВыиграл студент: %1").arg(winner));

    }
    else
    {
        QMessageBox::information(this, "Конкурс "+ contest,
                                 "Нет побидителя в этом конкурсе");
    }

    return winner;
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
    if (currentMode == ModeAttestat) {
        if (OnBudget() > 0) {
            accept();
        } else {
            QMessageBox::warning(this, "Результат", "Нет подходящих студентов.");
        }
    } else if (currentMode == ModeCurrent) {
        QString winner = onContest();
        if (!winner.isEmpty()) {
            accept();
        } else {
            QMessageBox::information(this, "Результат", "Нет победителя.");
        }
    }
}

void DialogContest::SerelizationDeserelization()
{
    // ATTESTAT METHOD
    QSettings settingsAttestat("StudManagARDA", "Attestat");

    ui->lineEditContest->setText(settingsAttestat.value("dialogContest/lineEditContest").toString());
    ui->lineEditFakyltet->setText(settingsAttestat.value("dialogContest/lineEditFakyltet").toString());
    ui->lineEditBall->setText(settingsAttestat.value("dialogContest/lineEditBall").toString());
    ui->lineEditFile->setText(settingsAttestat.value("dialogContest/lineEditFile").toString());
    ui->lineEditFileSave->setText(settingsAttestat.value("dialogContest/lineEditFileSave").toString());

    connect(ui->lineEditContest, &QLineEdit::textChanged, this, [](const QString &text){
        QSettings settings("StudManagARDA", "Attestat");
        settings.setValue("dialogContest/lineEditContest", text);
    });
    connect(ui->lineEditFakyltet, &QLineEdit::textChanged, this, [](const QString &text){
        QSettings settings("StudManagARDA", "Attestat");
        settings.setValue("dialogContest/lineEditFakyltet", text);
    });
    connect(ui->lineEditBall, &QLineEdit::textChanged, this, [](const QString &text){
        QSettings settings("StudManagARDA", "Attestat");
        settings.setValue("dialogContest/lineEditBall", text);
    });
    connect(ui->lineEditFile, &QLineEdit::textChanged, this, [](const QString &text){
        QSettings settings("StudManagARDA", "Attestat");
        settings.setValue("dialogContest/lineEditFile", text);
    });
    connect(ui->lineEditFileSave, &QLineEdit::textChanged, this, [](const QString &text){
        QSettings settings("StudManagARDA", "Attestat");
        settings.setValue("dialogContest/lineEditFileSave", text);
    });
    //end attestat serelization


    QSettings settingsContest("StudManagARDA", "ContestMethod");

    ui->lineEditFileSaveContest->setText(settingsContest.value("CurretContest/lineEditFileSaveContest").toString());
    ui->lineEditFileLogContest->setText(settingsContest.value("CurretContest/lineEditFileLogContest").toString());
    ui->lineEditContest->setText(settingsContest.value("CurretContest/lineEditContest").toString());
    ui->lineEditFileInputContest ->setText(settingsContest.value("CurretContest/lineEditFileInputContest").toString());

    connect(ui->lineEditFileSaveContest,&QLineEdit::textChanged,this,[](const QString& text){
        QSettings settings("StudManagARDA","ContestMethod");
        settings.setValue("CurretContest/lineEditFileSaveContest",text);
    });

    connect(ui->lineEditFileLogContest, &QLineEdit::textChanged, this, [](const QString &text){
        QSettings settings("StudManagARDA", "ContestMethod");
        settings.setValue("CurretContest/lineEditFileLogContest", text);
    });
    connect(ui->lineEditContest, &QLineEdit::textChanged, this, [](const QString &text){
        QSettings settings("StudManagARDA", "ContestMethod");
        settings.setValue("CurretContest/lineEditContest", text);
    });
    connect(ui->lineEditFileInputContest, &QLineEdit::textChanged, this, [](const QString &text){
        QSettings settings("StudManagARDA", "ContestMethod");
        settings.setValue("CurretContest/lineEditFileInputContest", text);
    });

}

