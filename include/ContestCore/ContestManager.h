/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#ifndef CONTESTMANAGER_H
#define CONTESTMANAGER_H

#include <QString>
#include "Contest.h"
#include "../Logger.h"

class ContestManager
{
   std::shared_ptr<Log> logger;

public:
   explicit ContestManager(const QString& logFile)
       : logger(Log::create(logFile.toStdString()))
   {}

public:
    ContestResult runContestAttestat(IAttestatContest &contest,
                    const QString &studentFile,
                    const QString &saveFile,
                    double budgetThreshold,
                    double contractThreshold,
                    int budgetSlots,
                    const QString &faculty);

    ContestResult runContestMaxScore(IMaxContest &contest,
                                     const QString &studentFile,
                                     const QString &saveFile,
                                     const QString &faculty);
    ContestResult runContestEge(IEgeContest& contest,
                                const QString& studentFile,
                                const QString& saveFile,
                                const QString& faculty,
                                double budgetThreshold,
                                double contractThreshold,
                                int budgetSlots);
};

#endif // CONTESTMANAGER_H
