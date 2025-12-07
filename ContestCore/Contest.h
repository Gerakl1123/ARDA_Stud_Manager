/*
 * Project: ARDA Student Manager
 * Author: German Niyazyan (Gerakl1123)
 * License: CC BY-NC 4.0 — Non-commercial use only
 *
 * © 2025 German Niyazyan
 * https://github.com/Gerakl1123/ARDA_Stud_Manager
 * https://creativecommons.org/licenses/by-nc/4.0/
 */


#ifndef CONTEST_H
#define CONTEST_H

#include <vector>
#include <memory>
#include <QString>
#include "../StudentManagerCore/Student.h"
#include "ContestResult.h"

class ContestBase
{
public:
    virtual ~ContestBase() = default;

    virtual void setStudents(const std::vector<std::shared_ptr<Student>>& students)=0;

};


class IMaxContest : public ContestBase
{
public:

    virtual ContestResult MaxScore() =0;

    virtual ~IMaxContest() = default;
};

class IAttestatContest : public ContestBase
{
public:
    virtual ContestResult evaluate(double budgetThreshold,double contractThreshold,int budgetSlots,int contractSlots)=0;

    virtual ~IAttestatContest() = default;
};


#endif // CONTEST_H
