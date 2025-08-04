/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#include "dialogcontest.h"
#include "ui_dialogcontest.h"
#include"ContestCore/ContestManager.h"
#include"ContestCore/AttestatContest.h"
#include"ContestCore/TopBallContest.h"
#include"Student.h"
#include"FileChooicer.h"
#include"BuildForm.h"

DialogContest::DialogContest(DialogMode mode, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogContest)
    , currentMode(mode)
{

    ui->setupUi(this);

    fileManager = std::make_unique<FileManager>(this);

    setWindowTitle("ПодМеню");

    FormBuilder temp;

    buttonLineEditPairs = temp.initializer(this);

    for (const auto& pair : buttonLineEditPairs) {
        setupBrowseButton(fileManager.get(),pair.first,pair.second);
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DialogContest::handleAccepted);
    connect(ui->pushButtonInfoAttestat, &QPushButton::clicked, this, [this] {
        QMessageBox::information(this, "📋 Информация о конкурсе",
                                 "Перед началом работы, пожалуйста, заполните следующие поля:\n\n"
                                 "📁 Файл со списком студентов\n"
                                 "💾 Файл для сохранения результатов (например: ФайлБюджет.txt / ФайлКоммерция.txt)\n"
                                 "🏫 Название факультета\n"
                                 "🎯 Количество бюджетных мест\n"
                                 "📊 Проходной балл на бюджет\n"
                                 "💼 Проходной балл на контракт\n\n"
                                 "✅ После заполнения всех данных нажмите кнопку для запуска конкурса.");
    });

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
        serelizer.DataSerelization(this,ModeSerelization::MaxScore);

        for(int i = 0; i< ui->gridLayout->count();++i)
        {
            QWidget* w = ui->gridLayout->itemAt(i)->widget();
            if(w)
            {
                w->hide();
                ui->pushButtonInfoAttestat->hide();
            }
        }
        break;
    case ModeAttestat:

        serelizer.DataSerelization(this,ModeSerelization::Attestat);

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

bool DialogContest::OnBudget()
{

    ContestResult result;

    QString QFakyltet = ui->lineEdit_Attestat_Fakyltet->text();
    QString file = ui->lineEdit_Attestat_InputFile->text();
    QString savefile = ui->lineEdit_Attestat_FileSave->text();
    QString logFile = ui->lineEdit_Attestat_FileLog ->text();
    QString BudgetMinBall = ui->lineEdit_Attestat_BudgetMinBall->text();
    QString ContractMinBall = ui->lineEdit_Attestat_ContractMinBall->text();
    QString slotsBudget = ui->lineEdit_Attestat_BudgetSlots->text();


    ContestManager manager(logFile);

    bool ok1 = true;
    bool ok2 = true;
    bool ok3 = true;

    double budget = BudgetMinBall.toDouble(&ok1);
    double contract = ContractMinBall.toDouble(&ok2);
    double SlotBudget = slotsBudget.toInt(&ok3);

    if (!ok1 || !ok2 || !ok3) {
        QMessageBox::warning(this, "Ошибка", "Некорректные значения проходных баллов");
        return false;
    }
    AttestatContest contest;

    result = manager.runContestAttestat(contest,file,savefile,budget,contract,SlotBudget,QFakyltet);

    if(!result.budget.empty())
    {
        QMessageBox::information(this, "Конкурс Аттестатов",QString("Данные добавлены в файл"));

    }else
    {
        QMessageBox::information(this, "Конкурс Аттестатов",
                                 "Нет студентов попавших на бюджет");
    }


    return !result.winnerInfo.empty();;

}

bool DialogContest::onMaxScore()
{

    ContestResult result;

    QString studentFile = ui->lineEdit_MaxScore_FileInput->text();
    QString fileSave = ui->lineEdit_MaxScore_FileSave->text();
    QString faculty = ui->lineEdit_MaxScore_Faculty->text();
    QString LogFile = ui->lineEdit_MaxScore_FileLog->text();

    ContestManager manager(LogFile);

    TopBallContest contest;

    result = manager.runContestMaxScore(contest,studentFile,fileSave,faculty);

    if(!result.winnerInfo.empty())
    {
        const Student& winner = *result.winnerInfo.at(0);

        QMessageBox::information(this,
                                 "Конкурс Высший Балл",
                                 QString("Данные добавлены в файл.\nВыиграл студент: %1 с баллом %2")
                                     .arg(QString::fromStdString(winner.name))
                                     .arg(winner.ball));

    }else
    {
        QMessageBox::information(this, "Конкурс Высший Балл",
                                 "Нет побидителя в этом конкурсе");
    }

    return !result.winnerInfo.empty();

}


void DialogContest::handleAccepted()
{
    if (currentMode == ModeAttestat) {
        if (OnBudget()) {
            accept();
        } else {
            QMessageBox::warning(this, "Результат", "Нет подходящих студентов.");
        }
    } else if (currentMode == ModeCurrent) {
        if (onMaxScore()) {
            accept();
        } else {
            QMessageBox::information(this, "Результат", "Нет победителя.");
        }
    }
}


void DialogContest::setupBrowseButton(FileManager *fileManager,QLineEdit* line, QPushButton* btn)
{
    FormBuilder::setupBrowseButton(btn,line,fileManager);

}
