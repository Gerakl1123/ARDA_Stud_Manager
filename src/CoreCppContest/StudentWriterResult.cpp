/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#include"../../include/ContestCore/StudentWriterResult.h"
#include <QTextStream>
#include"../../include/ContestCore/Loader.h"
#include<QDateTime>
void StudentWritter::writeResultContestAttestat(const QString &file,
                                        ContestResult &result,
                                        const QString &faculty)
{
    QFile ofile(file);


    if(!ofile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&ofile);

    out << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << "] " << "\n";

    out<< "Факультет - " << faculty << " !!!\n";

    out << "\n-- Бюджетники --\n";
    for (const auto& s : result.budget)
        out << QString::fromStdString(s->name) << " " << s->ball << "\n";

    out << "\n-- Контратники --\n";
    for (const auto& s : result.contract)
        out << QString::fromStdString(s->name) << " " << s->ball << "\n";

    out << "\n-- Непоступившые --\n";
    for (const auto& s : result.reject)
        out << QString::fromStdString(s->name) << " " << s->ball << "\n";

    ofile.close();
}

void StudentWritter::writeResultContestMaxScore(const QString &file, ContestResult &result, const QString &faculty)
{

    QFile ofile(file);


    if(!ofile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&ofile);

    out << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << "] " << "\n";

    out<< "Факультет - " << faculty << " !!!\n";

    out << "\n-- Победитель --\n";

    if (!result.winnerInfo.empty())
    {
        const Student& winner = *result.winnerInfo[0];

        out << QString::fromStdString(winner.name) << " "
            << winner.ball << "\n";
    }
    else
    {
        out << "Нет победителя.\n";
    }

    ofile.close();
}


void StudentWritter::writeResultContestEge(const QString &file, ContestResult &result, const QString &faculty)
{

    QFile ofile(file);

    try
    {
        Validator::isFileValid(ofile,ModeValidator::WriteFile);

    }
    catch(const std::logic_error& e)
    {
        qWarning() << "Не удалось открыть файл для записи:" << ofile.fileName();
        return;
    }

    QTextStream out(&ofile);

    out << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << "] " << "\n";

    out<< " Факультет " + faculty <<"\n";
    out<< " Бюджетники " <<"\n";

    for(const auto& s : result.budgetEge)
    {
        out<<QString::fromStdString(s->name)<< " " << s->ball<<"\n";
    }
    out<< " Коммерция " <<"\n";

    for(const auto& s : result.contractEge)
    {
        out<<QString::fromStdString(s->name)<< " " << s->ball<<"\n";
    }
    out<< " Непоступившие " <<"\n";

    for(const auto& s : result.rejectEge)
    {
        out<<QString::fromStdString(s->name)<< " " << s->ball<<"\n";
    }
    ofile.close();


}
