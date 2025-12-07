/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#ifndef STUDENTWRITERRESULT_H
#define STUDENTWRITERRESULT_H

#include <QString>
#include <vector>
#include <memory>
#include<QFile>
#include "../StudentManagerCore/Student.h"
#include "ContestResult.h"

class StudentWritter
{
public:
    static void writeResultContestAttestat(const QString& file,ContestResult& result, const QString& faculty);
    static void writeResultContestMaxScore(const QString& file,ContestResult& result, const QString& faculty);

};

#endif // STUDENTWRITERRESULT_H
