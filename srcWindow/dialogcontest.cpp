#include "dialogcontest.h"
#include "ui_dialogcontest.h"

DialogContest::DialogContest(DialogMode mode, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogContest)
    , currentMode(mode)
{
    ui->setupUi(this);


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
    QString QFakyltet = ui->lineEditFakyltet->text();
    QString ballSTR = ui->lineEditBall->text();
    QString file = ui->lineEditFile->text();
    QString savefile = ui->lineEditFileSave->text();
    QString logFile = ui->lineEditFileLogAttestat ->text();

    std::string log = logFile.toStdString();

    Attestat contestAttestat(log);

    bool ok = true;
    double ballValue = ballSTR.toDouble(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Некорректное значение балла");
        return -1;
    }

    qint16 count =  contestAttestat.findWinner(ballValue, file, savefile, QFakyltet);

    if(count)
        QMessageBox::information(this, "Конкурс Аттестатов",
                             QString("Данные добавлены в файл.\nПоступило: %1 студентов").arg(count));
    else
        QMessageBox::information(this, "Конкурс Аттестатов",
                                 "Нет студентов соответствующих этим критериям");

    return count;
}

Student DialogContest::onContest()
{

    QString inputFile = ui->lineEditFileInputContest->text();
    QString fileSave = ui->lineEditFileSaveContest->text();
    QString LogFile = ui->lineEditFileLogContest->text();

    std::string logA = LogFile.toStdString();

    TopContest topCon(logA);

   Student winner = topCon.TopBall(inputFile,fileSave);

    if(!winner.empty())
    {
       QMessageBox::information(this,
                                "Конкурс Высший Балл" ,
                                QString("Данные добавлены в файл.\nВыиграл студент: %1 с баллом %2")
                                     .arg(winner.name)
                                     .arg(winner.ball));
    }

    else
    {
        QMessageBox::information(this, "Конкурс Высший Балл",
                                 "Нет побидителя в этом конкурсе");
    }

    return winner;
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
        Student winner = onContest();
        if (!winner.empty()) {
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
    ui->lineEditFileLogAttestat->setText(settingsAttestat.value("dialogContest/lineEditFileLogAttestat").toString());
    ui->lineEditFakyltet->setText(settingsAttestat.value("dialogContest/lineEditFakyltet").toString());
    ui->lineEditBall->setText(settingsAttestat.value("dialogContest/lineEditBall").toString());
    ui->lineEditFile->setText(settingsAttestat.value("dialogContest/lineEditFile").toString());
    ui->lineEditFileSave->setText(settingsAttestat.value("dialogContest/lineEditFileSave").toString());

    connect(ui->lineEditFileLogAttestat, &QLineEdit::textChanged, this, [](const QString &text){
        QSettings settings("StudManagARDA", "Attestat");
        settings.setValue("dialogContest/lineEditFileLogAttestat", text);
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
    ui->lineEditFileInputContest ->setText(settingsContest.value("CurretContest/lineEditFileInputContest").toString());

    connect(ui->lineEditFileSaveContest,&QLineEdit::textChanged,this,[](const QString& text){
        QSettings settings("StudManagARDA","ContestMethod");
        settings.setValue("CurretContest/lineEditFileSaveContest",text);
    });

    connect(ui->lineEditFileLogContest, &QLineEdit::textChanged, this, [](const QString &text){
        QSettings settings("StudManagARDA", "ContestMethod");
        settings.setValue("CurretContest/lineEditFileLogContest", text);
    });
    connect(ui->lineEditFileInputContest, &QLineEdit::textChanged, this, [](const QString &text){
        QSettings settings("StudManagARDA", "ContestMethod");
        settings.setValue("CurretContest/lineEditFileInputContest", text);
    });

}

