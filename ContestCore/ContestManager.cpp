/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#include "ContestManager.h"
#include "../Loader.h"
#include "StudentWriterResult.h"

ContestResult ContestManager::runContestAttestat(IAttestatContest &contest, const QString &studentFile, const QString &saveFile, double budgetThreshold, double contractThreshold, int budgetSlots,int contracrSlots, const QString &faculty)
{
    logger->write("Loading students from " + studentFile.toStdString());

    auto stud = StudentLoader::fromFile(studentFile);

    contest.setStudents(stud);

    logger->write("Running contest Attestat");

    ContestResult result = contest.evaluate(budgetThreshold, contractThreshold, budgetSlots,contracrSlots);

    logger->write("Writing results to " + saveFile.toStdString());

    StudentWritter::writeResultContestAttestat(saveFile, result, faculty);

    logger->write("Contest finished successfully");

    return result;
}

ContestResult ContestManager::runContestMaxScore(IMaxContest &contest, const QString &studentFile, const QString &saveFile, const QString &faculty)
{
    logger->write("Loading students from " + studentFile.toStdString());

    auto stud = StudentLoader::fromFile(studentFile);

    contest.setStudents(stud);

    logger->write("Running contest MaxScore");

    ContestResult result = contest.MaxScore();

    logger->write("Writing results to " + saveFile.toStdString());

    StudentWritter::writeResultContestMaxScore(saveFile,result,faculty);

    logger->write("Contest finished successfully");

    return result;
}
